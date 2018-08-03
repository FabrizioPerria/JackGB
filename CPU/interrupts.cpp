#include "interrupts.h"

PIC::PIC()
{
}

void PIC::Step()
{
    if(_master && _enable && _flags) {
        unsigned char set = _enable & _flags;

        if(set & INTERRUPTS_VBLANK) {
            _flags &= ~INTERRUPTS_VBLANK;
            //vblank();
        }

        if(set & INTERRUPTS_LCDSTAT) {
            _flags &= ~INTERRUPTS_LCDSTAT;
            //lcdStat();
        }

        if(set & INTERRUPTS_TIMER) {
            _flags &= ~INTERRUPTS_TIMER;
            //timer();
        }

        if(set & INTERRUPTS_SERIAL) {
            _flags &= ~INTERRUPTS_SERIAL;
            //serial();
        }

        if(set & INTERRUPTS_JOYPAD) {
            _flags &= ~INTERRUPTS_JOYPAD;
            //joypad();
        }
    }
}

void PIC::Reset()
{
    _master = 1;
    _enable = 0;
    _flags = 0;
}
