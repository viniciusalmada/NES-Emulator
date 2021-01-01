#ifndef NES_CPU_H
#define NES_CPU_H

#include <string>
#include <functional>
#include "Typedefs.h"

class Bus;

class CPU {
public:
    CPU();

    ~CPU();

    // Link the CPU to Bus
    void connectBus(Bus* n) { bus = n; }

public:
    // CPU Core registers. All that 6502 has.
    Bits8 mA = 0x00;  // Accumulator Register
    Bits8 mX = 0x00;  // X Register
    Bits8 mY = 0x00;  // Y Register
    Bits8 mSTKP = 0x00;  // Stack Pointer (points to location on bus)
    Bits16 mPC = 0x0000;  // Program counter
    Bits8 mStatus = 0x00;  // Status Register

    // Signal that represents hardware events
    void clock(); // Make mA single one clock cycle

    void reset();

    void irq(); // Interrupt request

    void nmi(); // Non-maskable Interrupt Request

    // Indicates the current instruction has completed, returning true.
    // This avoid the clocking manually.
    bool complete();

    // The status register structure
    // C Z I D B U V N
    // 0 1 2 3 4 5 6 7
    enum StatesReg {
        C = (1 << 0),   // Carry bit
        Z = (1 << 1),   // Zero
        I = (1 << 2),   // Disable Interrupts
        D = (1 << 3),   // Decimal Mode
        B = (1 << 4),   // Break
        U = (1 << 5),   // Unused
        V = (1 << 6),   // Overflow
        N = (1 << 7),   // Negative
    };

    // Utilities functions
    Bits8 fetchData();

private:
    // Functions to access status register
    Bits8 getFlag(StatesReg flag) const;

    void setFlag(StatesReg flag, bool v);

    // Auxiliary properties to use in emulation
    Bits8 mFetched = 0x00;   // Represents the working input value to the ALU
    Bits16 temp = 0x0000;    // A convenience variable used everywhere
    Bits16 mAddrAbs = 0x0000;    // All used memory addresses end up here
    Bits16 mAddrRel = 0x0000;    // Represents absolute address following mA branch
    Bits8 opcode = 0x00;    // Is the instruction byte
    Bits8 mCycles = 0x00;    // Counts how many mCycles the instruction has remaining
    Bits32 mClockCount = 0x00000000;    // Counts how many mCycles the instruction has remaining

    // To make Bus communication
    Bus* bus = nullptr;

    Bits8 read(Bits16 addr);

    void write(Bits16 addr, Bits8 data);

    // Instructions to represents an opcode.
    struct Instruction {
        std::string name;
        std::function<Bits8(CPU*)> operate;
        std::function<Bits8(CPU*)> addrMode;
        Bits8 cycles = 0;
    };

    // Lookup table with all 256 possible opcodes.
    // The access to it can be done through mA single Byte:
    // The first 4 bits to row, and the other 4 bits, to get column;
    std::array<std::array<Instruction, 16>, 16> lookupTable;

private:

    // Addressing Modes =============================================
    // The 6502 has mA variety of addressing modes to access data in
    // memory, some of which are direct and some are indirect (like
    // pointers in C++). Each opcode contains information about which
    // addressing mode should be employed to facilitate the
    // instruction, in regards to where it reads/writes the data it
    // uses. The address mode changes the number of bytes that
    // makes up the full instruction, so we implement addressing
    // before executing the instruction, to make sure the program
    // counter is at the correct location, the instruction is
    // primed with the addresses it needs, and the number of clock
    // mCycles the instruction requires is calculated. These functions
    // may adjust the number of mCycles required depending upon where
    // and how the memory is accessed, so they return the required
    // adjustment.
    // From @javidx9
    Bits8 IMP();

    Bits8 IMM();

    Bits8 ZP0();

    Bits8 ZPX();

    Bits8 ZPY();

    Bits8 REL();

    Bits8 ABS();

    Bits8 ABX();

    Bits8 ABY();

    Bits8 IND();

    Bits8 IZX();

    Bits8 IZY();

    // Opcodes ======================================================
    // There are 56 "legitimate" opcodes provided by the 6502 CPU. I
    // have not modelled "unofficial" opcodes. As each opcode is
    // defined by 1 byte, there are potentially 256 possible codes.
    // Codes are not used in mA "switch case" style on mA processor,
    // instead they are responsible for switching individual parts of
    // CPU circuits on and off. The opcodes listed here are official,
    // meaning that the functionality of the chip when provided with
    // these codes is as the developers intended it to be. Unofficial
    // codes will of course also influence the CPU circuitry in
    // interesting ways, and can be exploited to gain additional
    // functionality!
    //
    // These functions return 0 normally, but some are capable of
    // requiring more clock mCycles when executed under certain
    // conditions combined with certain addressing modes. If that is
    // the case, they return 1.
    //
    // I have included detailed explanations of each function in
    // the class implementation file. Note they are listed in
    // alphabetical order here for ease of finding.
    // From @javidx9
    Bits8 ADC();

    Bits8 AND();

    Bits8 ASL();

    Bits8 BCC();

    Bits8 BCS();

    Bits8 BEQ();

    Bits8 BIT();

    Bits8 BMI();

    Bits8 BNE();

    Bits8 BPL();

    Bits8 BRK();

    Bits8 BVC();

    Bits8 BVS();

    Bits8 CLC();

    Bits8 CLD();

    Bits8 CLI();

    Bits8 CLV();

    Bits8 CMP();

    Bits8 CPX();

    Bits8 CPY();

    Bits8 DEC();

    Bits8 DEX();

    Bits8 DEY();

    Bits8 EOR();

    Bits8 INC();

    Bits8 INX();

    Bits8 INY();

    Bits8 JMP();

    Bits8 JSR();

    Bits8 LDA();

    Bits8 LDX();

    Bits8 LDY();

    Bits8 LSR();

    Bits8 NOP();

    Bits8 ORA();

    Bits8 PHA();

    Bits8 PHP();

    Bits8 PLA();

    Bits8 PLP();

    Bits8 ROL();

    Bits8 ROR();

    Bits8 RTI();

    Bits8 RTS();

    Bits8 SBC();

    Bits8 SEC();

    Bits8 SED();

    Bits8 SEI();

    Bits8 STA();

    Bits8 STX();

    Bits8 STY();

    Bits8 TAX();

    Bits8 TAY();

    Bits8 TSX();

    Bits8 TXA();

    Bits8 TXS();

    Bits8 TYA();

    Bits8 XXX();
};


#endif //NES_CPU_H
