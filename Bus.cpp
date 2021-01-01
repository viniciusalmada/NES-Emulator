#include "Bus.h"

Bus::Bus() {
    // Clear RAM content
    for (auto& i : ram) i = 0x00;

    cpu.connectBus(this);
}

Bus::~Bus() = default;

void Bus::write(Bits16 addr, Bits8 data) {
    if (addr <= 0xFFFF)
        ram[addr] = data;

}

Bits8 Bus::read(Bits16 addr, bool readOnly) {
    if (addr <= 0xFFFF)
        return ram[addr];

    return 0x00;
}
