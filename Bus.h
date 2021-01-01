#ifndef NES_BUS_H
#define NES_BUS_H

#include <array>
#include "CPU.h"
#include "Typedefs.h"

class Bus {
    Bus();

    ~Bus();

public: // Devices on Bus
    CPU cpu;

    // Fake RAM 64 KB
    std::array<Bits8, 64 * 1024> ram{};

public: // Read and Write functions
    void write(Bits16 addr, Bits8 data);

    Bits8 read(Bits16 addr, bool readOnly = false);
};


#endif //NES_BUS_H
