#pragma once

enum Interrupt
{
    INTERRUPTS_VBLANK = 1,
    INTERRUPTS_LCDSTAT = 2,
    INTERRUPTS_TIMER = 4,
    INTERRUPTS_SERIAL = 8,
    INTERRUPTS_JOYPAD = 16,
};

class PIC
{
public:
    PIC();

    void Step();
    void Reset();

private:
    unsigned char _master;
    unsigned char _enable;
    unsigned char _flags;
};
