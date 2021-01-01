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

    void connectBus(Bus* n) { bus = n; }

public: // Register
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

    Bits8 a = 0x00;  // Accumulator Register
    Bits8 x = 0x00;  // X Register
    Bits8 y = 0x00;  // Y Register
    Bits8 stkp = 0x00;  // Stack Pointer
    Bits16 pc = 0x0000;  // Program counter
    Bits8 currentStatus = 0x00;  // Status Register

    // Addressing Modes
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

    // OpCodes
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

    // Signals
    void clock();

    void reset();

    void irq();

    void nmi();

    // Utilities functions
    Bits8 fetchData();

    Bits8 fetched = 0x00;

    Bits16 addrAbs = 0x0000;
    Bits16 addrRel = 0x0000;
    Bits8 opcode = 0x00;
    Bits8 cycles = 0x00;

private:
    Bus* bus = nullptr;

    Bits8 read(Bits16 addr);

    void write(Bits16 addr, Bits8 data);

    // Functions to access status register
    Bits8 getFlag(StatesReg f);

    void setFlag(StatesReg f, bool v);

    struct Instruction {
        std::string name;
        std::function<Bits8(CPU*)> operate;
        std::function<Bits8(CPU*)> addrMode;
        Bits8 cycles = 0;
    };

    std::array<std::array<Instruction, 16>, 16> lookupTable;
};


#endif //NES_CPU_H
