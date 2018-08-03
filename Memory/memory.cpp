#include "memory.h"
#include <cstring>
#include <assert.h>
#include "ROM/rom.h"

Memory::Memory()
{
}

void Memory::WriteByte(unsigned char data, unsigned short address)
{
    _mem[address] = data;
}

void Memory::WriteWord(unsigned short data, unsigned short address)
{
    _mem[address] 		= data 			& 0xFF;
    _mem[address + 1] 	= (data >> 8) 	& 0xFF;
}

unsigned char Memory::ReadByte(unsigned short address)
{
    return _mem[address];
}

unsigned short Memory::ReadWord(unsigned short address)
{
    unsigned short tmp = 0;
    tmp = _mem[address + 1] << 8;
    tmp += _mem[address];
    return tmp;
}

void Memory::Copy(unsigned short destination, const unsigned char* source, const unsigned short length)
{
    for(unsigned short i = 0; i < length; ++i)
        _mem[destination + i] = source[i];
}

void Memory::Memset(unsigned short destination, unsigned char value, const unsigned short length)
{
    for(unsigned short i = 0; i < length; ++i)
        _mem[destination + i] = value;
}

void Memory::Reset()
{
    Memset(0, 0, 0xFFFF);
    Copy(0, ioReset, 0x150);

    WriteByte(0xFF05, 0);
    WriteByte(0xFF06, 0);
    WriteByte(0xFF07, 0);
    WriteByte(0xFF10, 0x80);
    WriteByte(0xFF11, 0xBF);
    WriteByte(0xFF12, 0xF3);
    WriteByte(0xFF14, 0xBF);
    WriteByte(0xFF16, 0x3F);
    WriteByte(0xFF17, 0x00);
    WriteByte(0xFF19, 0xBF);
    WriteByte(0xFF1A, 0x7A);
    WriteByte(0xFF1B, 0xFF);
    WriteByte(0xFF1C, 0x9F);
    WriteByte(0xFF1E, 0xBF);
    WriteByte(0xFF20, 0xFF);
    WriteByte(0xFF21, 0x00);
    WriteByte(0xFF22, 0x00);
    WriteByte(0xFF23, 0xBF);
    WriteByte(0xFF24, 0x77);
    WriteByte(0xFF25, 0xF3);
    WriteByte(0xFF26, 0xF1);
    WriteByte(0xFF40, 0x91);
    WriteByte(0xFF42, 0x00);
    WriteByte(0xFF43, 0x00);
    WriteByte(0xFF45, 0x00);
    WriteByte(0xFF47, 0xFC);
    WriteByte(0xFF48, 0xFF);
    WriteByte(0xFF49, 0xFF);
    WriteByte(0xFF4A, 0x00);
    WriteByte(0xFF4B, 0x00);
    WriteByte(0xFFFF, 0x00);
}
