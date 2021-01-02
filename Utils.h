#ifndef NES_UTILS_H
#define NES_UTILS_H

typedef uint8_t Bits8;
typedef uint16_t Bits16;
typedef uint32_t Bits32;

// Auxiliary functions that use bitwise operations.
static Bits8 highB(Bits8 b) {
    return (b & 0xF0) >> 4;
}

static Bits8 lowB(Bits8 b) {
    return b & 0x0F;
}

#endif //NES_UTILS_H
