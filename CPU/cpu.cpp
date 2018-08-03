#include "cpu.h"

CPU::CPU(Memory* memory) : _ticks(0), _stopped(0), _memory(memory)
{
}

void CPU::Step() {
    unsigned char instruction;
    unsigned short operand = 0;

    if(_stopped) return;

    instruction = _memory->ReadByte(_registers.pc++);

    if(instructions[instruction].nullable == nullptr)
        undefined();

    if(instructions[instruction].length == 1) operand = (unsigned short)_memory->ReadByte(_registers.pc);
    if(instructions[instruction].length == 2) operand = _memory->ReadWord(_registers.pc);
    _registers.pc += instructions[instruction].length;

    switch(instructions[instruction].length) {
        case 0:
            (this->*instructions[instruction].executeVoid)();
            break;

        case 1:
            (this->*instructions[instruction].executeChar)((unsigned char)operand);
            break;

        case 2:
            (this->*instructions[instruction].executeShort)(operand);
            break;
    }

    _ticks += instructions[instruction].ticks;
}

void CPU::Reset()
{
    _registers.a = 0x01;
    _registers.f = 0xb0;
    _registers.b = 0x00;
    _registers.c = 0x13;
    _registers.d = 0x00;
    _registers.e = 0xd8;
    _registers.h = 0x01;
    _registers.l = 0x4d;
    _registers.sp = 0xfffe;
    _registers.pc = 0x100;

    //memset(tiles, 0, sizeof(tiles));

    //backgroundPalette[0] = palette[0];
    //backgroundPalette[1] = palette[1];
    //backgroundPalette[2] = palette[2];
    //backgroundPalette[3] = palette[3];

    //spritePalette[0][0] = palette[0];
    //spritePalette[0][1] = palette[1];
    //spritePalette[0][2] = palette[2];
    //spritePalette[0][3] = palette[3];

    //spritePalette[1][0] = palette[0];
    //spritePalette[1][1] = palette[1];
    //spritePalette[1][2] = palette[2];
    //spritePalette[1][3] = palette[3];

    //gpu.control = 0;
    //gpu.scrollX = 0;
    //gpu.scrollY = 0;
    //gpu.scanline = 0;
    //gpu.tick = 0;

    _ticks = 0;
    _stopped = 0;

    //memset(framebuffer, 255, sizeof(framebuffer));


}

void CPU::writeToStack(unsigned short data)
{
    _memory->WriteWord(data, _registers.sp);
    _registers.sp += 2;
}

unsigned short CPU::readFromStack()
{
    unsigned short tmp = _memory->ReadWord(_registers.sp);
    _registers.sp -= 2;
    return tmp;
}
