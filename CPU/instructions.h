#pragma once
#include <cstdlib>

class CPU;

typedef void (CPU::*FPvoid)(void);
typedef void (CPU::*FPchar)(unsigned char);
typedef void (CPU::*FPshort)(unsigned short);

typedef struct instruction
{
    const char* instruction;
    unsigned char length;
    unsigned char ticks;
    union {
        FPshort executeShort;
        FPchar executeChar;
        FPvoid executeVoid;
        void* nullable;
    };
}instruction;
