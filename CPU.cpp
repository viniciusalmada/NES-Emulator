//
// Created by vinicius on 31/12/2020.
//

#include "CPU.h"
#include "Bus.h"

CPU::CPU() {
    auto NULL_INSTRUCTION = Instruction{"XXX", NULL, NULL, 0};
    lookupTable[0x0][0x0] = {"BRK", &CPU::BRK, &CPU::IMM, 7};
    lookupTable[0x0][0x1] = {"ORA", &CPU::ORA, &CPU::IZX, 6};
    lookupTable[0x0][0x2] = NULL_INSTRUCTION;
    lookupTable[0x0][0x3] = NULL_INSTRUCTION;
    lookupTable[0x0][0x4] = NULL_INSTRUCTION;
    lookupTable[0x0][0x5] = {"ORA", &CPU::ORA, &CPU::ZP0, 3};
    lookupTable[0x0][0x6] = {"ASL", &CPU::ASL, &CPU::ZP0, 5};
    lookupTable[0x0][0x7] = NULL_INSTRUCTION;
    lookupTable[0x0][0x8] = {"PHP", &CPU::PHP, &CPU::IMP, 3};
    lookupTable[0x0][0x9] = {"ORA", &CPU::ORA, &CPU::IMM, 2};
    lookupTable[0x0][0xA] = {"ASL", &CPU::ASL, &CPU::IMP, 2};
    lookupTable[0x0][0xB] = NULL_INSTRUCTION;
    lookupTable[0x0][0xC] = NULL_INSTRUCTION;
    lookupTable[0x0][0xD] = {"ORA", &CPU::ORA, &CPU::ABS, 4};
    lookupTable[0x0][0xE] = {"ASL", &CPU::ASL, &CPU::ABS, 6};
    lookupTable[0x0][0xF] = NULL_INSTRUCTION;

    lookupTable[0x1][0x0] = {"BPL", &CPU::BPL, &CPU::REL, 2};
    lookupTable[0x1][0x1] = {"ORA", &CPU::ORA, &CPU::IZY, 5};
    lookupTable[0x1][0x2] = NULL_INSTRUCTION;
    lookupTable[0x1][0x3] = NULL_INSTRUCTION;
    lookupTable[0x1][0x4] = NULL_INSTRUCTION;
    lookupTable[0x1][0x5] = {"ORA", &CPU::ORA, &CPU::ZPX, 4};
    lookupTable[0x1][0x6] = {"ASL", &CPU::ASL, &CPU::ZPX, 6};
    lookupTable[0x1][0x7] = NULL_INSTRUCTION;
    lookupTable[0x1][0x8] = {"CLC", &CPU::CLC, &CPU::IMP, 2};
    lookupTable[0x1][0x9] = {"ORA", &CPU::ORA, &CPU::ABY, 4};
    lookupTable[0x1][0xA] = NULL_INSTRUCTION;
    lookupTable[0x1][0xB] = NULL_INSTRUCTION;
    lookupTable[0x1][0xC] = NULL_INSTRUCTION;
    lookupTable[0x1][0xD] = {"ORA", &CPU::ORA, &CPU::ABX, 4};
    lookupTable[0x1][0xE] = {"ASL", &CPU::ASL, &CPU::ABX, 7};
    lookupTable[0x1][0xF] = NULL_INSTRUCTION;

    lookupTable[0x2][0x0] = {"JSR", &CPU::JSR, &CPU::ABS, 6};
    lookupTable[0x2][0x1] = {"AND", &CPU::AND, &CPU::IZX, 6};
    lookupTable[0x2][0x2] = NULL_INSTRUCTION;
    lookupTable[0x2][0x3] = NULL_INSTRUCTION;
    lookupTable[0x2][0x4] = {"BIT", &CPU::BIT, &CPU::ZP0, 3};
    lookupTable[0x2][0x5] = {"AND", &CPU::AND, &CPU::ZP0, 3};
    lookupTable[0x2][0x6] = {"ROL", &CPU::ROL, &CPU::ZP0, 5};
    lookupTable[0x2][0x7] = NULL_INSTRUCTION;
    lookupTable[0x2][0x8] = {"PLP", &CPU::PLP, &CPU::IMP, 4};
    lookupTable[0x2][0x9] = {"AND", &CPU::AND, &CPU::IMM, 2};
    lookupTable[0x2][0xA] = {"ROL", &CPU::ROL, &CPU::IMP, 2};
    lookupTable[0x2][0xB] = NULL_INSTRUCTION;
    lookupTable[0x2][0xC] = {"BIT", &CPU::BIT, &CPU::ABS, 4};
    lookupTable[0x2][0xD] = {"AND", &CPU::AND, &CPU::ABS, 4};
    lookupTable[0x2][0xE] = {"ROL", &CPU::ROL, &CPU::ABS, 6};
    lookupTable[0x2][0xF] = NULL_INSTRUCTION;

    lookupTable[0x3][0x0] = {"BMI", &CPU::BMI, &CPU::REL, 2};
    lookupTable[0x3][0x1] = {"AND", &CPU::AND, &CPU::IZY, 5};
    lookupTable[0x3][0x2] = NULL_INSTRUCTION;
    lookupTable[0x3][0x3] = NULL_INSTRUCTION;
    lookupTable[0x3][0x4] = NULL_INSTRUCTION;
    lookupTable[0x3][0x5] = {"AND", &CPU::AND, &CPU::ZPX, 4};
    lookupTable[0x3][0x6] = {"ROL", &CPU::ROL, &CPU::ZPX, 6};
    lookupTable[0x3][0x7] = NULL_INSTRUCTION;
    lookupTable[0x3][0x8] = {"SEC", &CPU::SEC, &CPU::IMP, 2};
    lookupTable[0x3][0x9] = {"AND", &CPU::AND, &CPU::ABY, 4};
    lookupTable[0x3][0xA] = NULL_INSTRUCTION;
    lookupTable[0x3][0xB] = NULL_INSTRUCTION;
    lookupTable[0x3][0xC] = NULL_INSTRUCTION;
    lookupTable[0x3][0xD] = {"AND", &CPU::AND, &CPU::ABX, 4};
    lookupTable[0x3][0xE] = {"ROL", &CPU::ROL, &CPU::ABX, 7};
    lookupTable[0x3][0xF] = NULL_INSTRUCTION;

    lookupTable[0x4][0x0] = {"RTI", &CPU::RTI, &CPU::IMP, 6};
    lookupTable[0x4][0x1] = {"EOR", &CPU::EOR, &CPU::IZX, 6};
    lookupTable[0x4][0x2] = NULL_INSTRUCTION;
    lookupTable[0x4][0x3] = NULL_INSTRUCTION;
    lookupTable[0x4][0x4] = NULL_INSTRUCTION;
    lookupTable[0x4][0x5] = {"EOR", &CPU::EOR, &CPU::ZP0, 3};
    lookupTable[0x4][0x6] = {"LSR", &CPU::LSR, &CPU::ZP0, 5};
    lookupTable[0x4][0x7] = NULL_INSTRUCTION;
    lookupTable[0x4][0x8] = {"PHA", &CPU::PHA, &CPU::IMP, 3};
    lookupTable[0x4][0x9] = {"EOR", &CPU::EOR, &CPU::IMM, 2};
    lookupTable[0x4][0xA] = {"LSR", &CPU::LSR, &CPU::IMP, 2};
    lookupTable[0x4][0xB] = NULL_INSTRUCTION;
    lookupTable[0x4][0xC] = {"JMP", &CPU::JMP, &CPU::ABS, 3};
    lookupTable[0x4][0xD] = {"EOR", &CPU::EOR, &CPU::ABS, 4};
    lookupTable[0x4][0xE] = {"LSR", &CPU::LSR, &CPU::ABS, 6};
    lookupTable[0x4][0xF] = NULL_INSTRUCTION;

    lookupTable[0x5][0x0] = {"BVC", &CPU::BVC, &CPU::REL, 2};
    lookupTable[0x5][0x1] = {"EOR", &CPU::EOR, &CPU::IZY, 5};
    lookupTable[0x5][0x2] = NULL_INSTRUCTION;
    lookupTable[0x5][0x3] = NULL_INSTRUCTION;
    lookupTable[0x5][0x4] = NULL_INSTRUCTION;
    lookupTable[0x5][0x5] = {"EOR", &CPU::EOR, &CPU::ZPX, 4};
    lookupTable[0x5][0x6] = {"LSR", &CPU::LSR, &CPU::ZPX, 6};
    lookupTable[0x5][0x7] = NULL_INSTRUCTION;
    lookupTable[0x5][0x8] = {"CLI", &CPU::CLI, &CPU::IMP, 2};
    lookupTable[0x5][0x9] = {"EOR", &CPU::EOR, &CPU::ABY, 4};
    lookupTable[0x5][0xA] = NULL_INSTRUCTION;
    lookupTable[0x5][0xB] = NULL_INSTRUCTION;
    lookupTable[0x5][0xC] = NULL_INSTRUCTION;
    lookupTable[0x5][0xD] = {"EOR", &CPU::EOR, &CPU::ABX, 4};
    lookupTable[0x5][0xE] = {"LSR", &CPU::LSR, &CPU::ABX, 7};
    lookupTable[0x5][0xF] = NULL_INSTRUCTION;

    lookupTable[0x6][0x0] = {"RTS", &CPU::RTS, &CPU::IMP, 6};
    lookupTable[0x6][0x1] = {"ADC", &CPU::ADC, &CPU::IZX, 6};
    lookupTable[0x6][0x2] = NULL_INSTRUCTION;
    lookupTable[0x6][0x3] = NULL_INSTRUCTION;
    lookupTable[0x6][0x4] = NULL_INSTRUCTION;
    lookupTable[0x6][0x5] = {"ADC", &CPU::ADC, &CPU::ZP0, 3};
    lookupTable[0x6][0x6] = {"ROR", &CPU::ROR, &CPU::ZP0, 5};
    lookupTable[0x6][0x7] = NULL_INSTRUCTION;
    lookupTable[0x6][0x8] = {"PLA", &CPU::PLA, &CPU::IMP, 4};
    lookupTable[0x6][0x9] = {"ADC", &CPU::ADC, &CPU::IMM, 2};
    lookupTable[0x6][0xA] = {"ROR", &CPU::ROR, &CPU::IMP, 2};
    lookupTable[0x6][0xB] = NULL_INSTRUCTION;
    lookupTable[0x6][0xC] = {"JMP", &CPU::JMP, &CPU::IND, 5};
    lookupTable[0x6][0xD] = {"ADC", &CPU::ADC, &CPU::ABS, 4};
    lookupTable[0x6][0xE] = {"ROR", &CPU::ROR, &CPU::ABS, 6};
    lookupTable[0x6][0xF] = NULL_INSTRUCTION;

    lookupTable[0x7][0x0] = {"BVS", &CPU::BVS, &CPU::REL, 2};
    lookupTable[0x7][0x1] = {"ADC", &CPU::ADC, &CPU::IZY, 5};
    lookupTable[0x7][0x2] = NULL_INSTRUCTION;
    lookupTable[0x7][0x3] = NULL_INSTRUCTION;
    lookupTable[0x7][0x4] = NULL_INSTRUCTION;
    lookupTable[0x7][0x5] = {"ADC", &CPU::ADC, &CPU::ZPX, 4};
    lookupTable[0x7][0x6] = {"ROR", &CPU::ROR, &CPU::ZPX, 6};
    lookupTable[0x7][0x7] = NULL_INSTRUCTION;
    lookupTable[0x7][0x8] = {"SEI", &CPU::SEI, &CPU::IMP, 2};
    lookupTable[0x7][0x9] = {"ADC", &CPU::ADC, &CPU::ABY, 4};
    lookupTable[0x7][0xA] = NULL_INSTRUCTION;
    lookupTable[0x7][0xB] = NULL_INSTRUCTION;
    lookupTable[0x7][0xC] = NULL_INSTRUCTION;
    lookupTable[0x7][0xD] = {"ADC", &CPU::ADC, &CPU::ABX, 4};
    lookupTable[0x7][0xE] = {"ROR", &CPU::ROR, &CPU::ABX, 7};
    lookupTable[0x7][0xF] = NULL_INSTRUCTION;

    lookupTable[0x8][0x0] = NULL_INSTRUCTION;
    lookupTable[0x8][0x1] = {"STA", &CPU::STA, &CPU::IZX, 6};
    lookupTable[0x8][0x2] = NULL_INSTRUCTION;
    lookupTable[0x8][0x3] = NULL_INSTRUCTION;
    lookupTable[0x8][0x4] = {"STY", &CPU::STY, &CPU::ZP0, 3};
    lookupTable[0x8][0x5] = {"STA", &CPU::STA, &CPU::ZP0, 3};
    lookupTable[0x8][0x6] = {"STX", &CPU::STX, &CPU::ZP0, 3};
    lookupTable[0x8][0x7] = NULL_INSTRUCTION;
    lookupTable[0x8][0x8] = {"DEY", &CPU::DEY, &CPU::IMP, 2};
    lookupTable[0x8][0x9] = NULL_INSTRUCTION;
    lookupTable[0x8][0xA] = {"TXA", &CPU::TXA, &CPU::IMP, 2};
    lookupTable[0x8][0xB] = NULL_INSTRUCTION;
    lookupTable[0x8][0xC] = {"STY", &CPU::STY, &CPU::ABS, 4};
    lookupTable[0x8][0xD] = {"STA", &CPU::STA, &CPU::ABS, 4};
    lookupTable[0x8][0xE] = {"STX", &CPU::STX, &CPU::ABS, 4};
    lookupTable[0x8][0xF] = NULL_INSTRUCTION;

    lookupTable[0x9][0x0] = {"BCC", &CPU::BCC, &CPU::REL, 2};
    lookupTable[0x9][0x1] = {"STA", &CPU::STA, &CPU::IZY, 6};
    lookupTable[0x9][0x2] = NULL_INSTRUCTION;
    lookupTable[0x9][0x3] = NULL_INSTRUCTION;
    lookupTable[0x9][0x4] = {"STY", &CPU::STY, &CPU::ZPX, 4};
    lookupTable[0x9][0x5] = {"STA", &CPU::STA, &CPU::ZPX, 4};
    lookupTable[0x9][0x6] = {"STX", &CPU::STX, &CPU::ZPY, 4};
    lookupTable[0x9][0x7] = NULL_INSTRUCTION;
    lookupTable[0x9][0x8] = {"TYA", &CPU::TYA, &CPU::IMP, 2};
    lookupTable[0x9][0x9] = {"STA", &CPU::STA, &CPU::ABY, 5};
    lookupTable[0x9][0xA] = {"TXS", &CPU::TXS, &CPU::IMP, 2};
    lookupTable[0x9][0xB] = NULL_INSTRUCTION;
    lookupTable[0x9][0xC] = NULL_INSTRUCTION;
    lookupTable[0x9][0xD] = {"STA", &CPU::STA, &CPU::ABX, 5};
    lookupTable[0x9][0xE] = NULL_INSTRUCTION;
    lookupTable[0x9][0xF] = NULL_INSTRUCTION;

    lookupTable[0xA][0x0] = {"LDY", &CPU::LDY, &CPU::IMM, 2};
    lookupTable[0xA][0x1] = {"LDA", &CPU::LDA, &CPU::IZX, 6};
    lookupTable[0xA][0x2] = {"LDX", &CPU::LDX, &CPU::IMM, 2};
    lookupTable[0xA][0x3] = NULL_INSTRUCTION;
    lookupTable[0xA][0x4] = {"LDY", &CPU::LDY, &CPU::ZP0, 3};
    lookupTable[0xA][0x5] = {"LDA", &CPU::LDA, &CPU::ZP0, 3};
    lookupTable[0xA][0x6] = {"LDX", &CPU::LDX, &CPU::ZP0, 3};
    lookupTable[0xA][0x7] = NULL_INSTRUCTION;
    lookupTable[0xA][0x8] = {"TAY", &CPU::TAY, &CPU::IMP, 2};
    lookupTable[0xA][0x9] = {"LDA", &CPU::LDA, &CPU::IMM, 2};
    lookupTable[0xA][0xA] = {"TAX", &CPU::TAX, &CPU::IMP, 2};
    lookupTable[0xA][0xB] = NULL_INSTRUCTION;
    lookupTable[0xA][0xC] = {"LDY", &CPU::LDY, &CPU::ABS, 4};
    lookupTable[0xA][0xD] = {"LDA", &CPU::LDA, &CPU::ABS, 4};
    lookupTable[0xA][0xE] = {"LDX", &CPU::LDX, &CPU::ABS, 4};
    lookupTable[0xA][0xF] = NULL_INSTRUCTION;

    lookupTable[0xB][0x0] = {"BCS", &CPU::BCS, &CPU::REL, 2};
    lookupTable[0xB][0x1] = {"LDA", &CPU::LDA, &CPU::IZY, 5};
    lookupTable[0xB][0x2] = NULL_INSTRUCTION;
    lookupTable[0xB][0x3] = NULL_INSTRUCTION;
    lookupTable[0xB][0x4] = {"LDY", &CPU::LDY, &CPU::ZPX, 4};
    lookupTable[0xB][0x5] = {"LDA", &CPU::LDA, &CPU::ZPX, 4};
    lookupTable[0xB][0x6] = {"LDX", &CPU::LDX, &CPU::ZPY, 4};
    lookupTable[0xB][0x7] = NULL_INSTRUCTION;
    lookupTable[0xB][0x8] = {"CLV", &CPU::CLV, &CPU::IMP, 2};
    lookupTable[0xB][0x9] = {"LDA", &CPU::LDA, &CPU::ABY, 4};
    lookupTable[0xB][0xA] = {"TSX", &CPU::TSX, &CPU::IMP, 2};
    lookupTable[0xB][0xB] = NULL_INSTRUCTION;
    lookupTable[0xB][0xC] = {"LDY", &CPU::LDY, &CPU::ABX, 4};
    lookupTable[0xB][0xD] = {"LDA", &CPU::LDA, &CPU::ABX, 4};
    lookupTable[0xB][0xE] = {"LDX", &CPU::LDX, &CPU::ABY, 4};
    lookupTable[0xB][0xF] = NULL_INSTRUCTION;

    lookupTable[0xC][0x0] = {"CPY", &CPU::CPY, &CPU::IMM, 2};
    lookupTable[0xC][0x1] = {"CMP", &CPU::CMP, &CPU::IZX, 6};
    lookupTable[0xC][0x2] = NULL_INSTRUCTION;
    lookupTable[0xC][0x3] = NULL_INSTRUCTION;
    lookupTable[0xC][0x4] = {"CPY", &CPU::CPY, &CPU::ZP0, 3};
    lookupTable[0xC][0x5] = {"CMP", &CPU::CMP, &CPU::ZP0, 3};
    lookupTable[0xC][0x6] = {"DEC", &CPU::DEC, &CPU::ZP0, 5};
    lookupTable[0xC][0x7] = NULL_INSTRUCTION;
    lookupTable[0xC][0x8] = {"INY", &CPU::INY, &CPU::IMP, 2};
    lookupTable[0xC][0x9] = {"CMP", &CPU::CMP, &CPU::IMM, 2};
    lookupTable[0xC][0xA] = {"DEX", &CPU::DEX, &CPU::IMP, 2};
    lookupTable[0xC][0xB] = NULL_INSTRUCTION;
    lookupTable[0xC][0xC] = {"CPY", &CPU::CPY, &CPU::ABS, 4};
    lookupTable[0xC][0xD] = {"CMP", &CPU::CMP, &CPU::ABS, 4};
    lookupTable[0xC][0xE] = {"DEC", &CPU::DEC, &CPU::ABS, 6};
    lookupTable[0xC][0xF] = NULL_INSTRUCTION;

    lookupTable[0xD][0x0] = {"BNE", &CPU::BNE, &CPU::REL, 2};
    lookupTable[0xD][0x1] = {"CMP", &CPU::CMP, &CPU::IZY, 5};
    lookupTable[0xD][0x2] = NULL_INSTRUCTION;
    lookupTable[0xD][0x3] = NULL_INSTRUCTION;
    lookupTable[0xD][0x4] = NULL_INSTRUCTION;
    lookupTable[0xD][0x5] = {"CMP", &CPU::CMP, &CPU::ZPX, 4};
    lookupTable[0xD][0x6] = {"DEC", &CPU::DEC, &CPU::ZPX, 6};
    lookupTable[0xD][0x7] = NULL_INSTRUCTION;
    lookupTable[0xD][0x8] = {"CLD", &CPU::CLD, &CPU::IMP, 2};
    lookupTable[0xD][0x9] = {"CMP", &CPU::CMP, &CPU::ABY, 4};
    lookupTable[0xD][0xA] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    lookupTable[0xD][0xB] = NULL_INSTRUCTION;
    lookupTable[0xD][0xC] = NULL_INSTRUCTION;
    lookupTable[0xD][0xD] = {"CMP", &CPU::CMP, &CPU::ABX, 4};
    lookupTable[0xD][0xE] = {"DEC", &CPU::DEC, &CPU::ABX, 7};
    lookupTable[0xD][0xF] = NULL_INSTRUCTION;

    lookupTable[0xE][0x0] = {"CPX", &CPU::CPX, &CPU::IMM, 2};
    lookupTable[0xE][0x1] = {"SBC", &CPU::SBC, &CPU::IZX, 6};
    lookupTable[0xE][0x2] = NULL_INSTRUCTION;
    lookupTable[0xE][0x3] = NULL_INSTRUCTION;
    lookupTable[0xE][0x4] = {"CPX", &CPU::CPX, &CPU::ZP0, 3};
    lookupTable[0xE][0x5] = {"SBC", &CPU::SBC, &CPU::ZP0, 3};
    lookupTable[0xE][0x6] = {"INC", &CPU::INC, &CPU::ZP0, 5};
    lookupTable[0xE][0x7] = NULL_INSTRUCTION;
    lookupTable[0xE][0x8] = {"INX", &CPU::INX, &CPU::IMP, 2};
    lookupTable[0xE][0x9] = {"SBC", &CPU::SBC, &CPU::IMM, 2};
    lookupTable[0xE][0xA] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    lookupTable[0xE][0xB] = NULL_INSTRUCTION;
    lookupTable[0xE][0xC] = {"CPX", &CPU::CPX, &CPU::ABS, 4};
    lookupTable[0xE][0xD] = {"SBC", &CPU::SBC, &CPU::ABS, 4};
    lookupTable[0xE][0xE] = {"INC", &CPU::INC, &CPU::ABS, 6};
    lookupTable[0xE][0xF] = NULL_INSTRUCTION;

    lookupTable[0xF][0x0] = {"BEQ", &CPU::BEQ, &CPU::REL, 2};
    lookupTable[0xF][0x1] = {"SBC", &CPU::SBC, &CPU::IZY, 5};
    lookupTable[0xF][0x2] = NULL_INSTRUCTION;
    lookupTable[0xF][0x3] = NULL_INSTRUCTION;
    lookupTable[0xF][0x4] = NULL_INSTRUCTION;
    lookupTable[0xF][0x5] = {"SBC", &CPU::SBC, &CPU::ZPX, 4};
    lookupTable[0xF][0x6] = {"INC", &CPU::INC, &CPU::ZPX, 6};
    lookupTable[0xF][0x7] = NULL_INSTRUCTION;
    lookupTable[0xF][0x8] = {"SED", &CPU::SED, &CPU::IMP, 2};
    lookupTable[0xF][0x9] = {"SBC", &CPU::SBC, &CPU::ABY, 4};
    lookupTable[0xF][0xA] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    lookupTable[0xF][0xB] = NULL_INSTRUCTION;
    lookupTable[0xF][0xC] = NULL_INSTRUCTION;
    lookupTable[0xF][0xD] = {"SBC", &CPU::SBC, &CPU::ABX, 4};
    lookupTable[0xF][0xE] = {"INC", &CPU::INC, &CPU::ABX, 7};
    lookupTable[0xF][0xF] = NULL_INSTRUCTION;
}

Bits8 CPU::read(Bits16 addr) {
    return bus->read(addr, false);
}

void CPU::write(Bits16 addr, Bits8 data) {
    bus->write(addr, data);
}

void CPU::clock() {
    if (cycles == 0) {
        opcode = read(pc);
        pc++;

        Bits8 opRow = (opcode & 0xF0) >> 4;
        Bits8 opCol = (opcode & 0x0F);

        // Get starting number of cycles
        cycles = lookupTable[opRow][opCol].cycles;
        Bits8 addCycleAddr = lookupTable[opRow][opCol].addrMode(this);
        Bits8 addCycleOp = lookupTable[opRow][opCol].operate(this);

        cycles += addCycleAddr & addCycleOp;
    }

    cycles--;
}