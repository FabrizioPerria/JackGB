#pragma once

typedef enum Section {
    RESET_IO = 0x0000,
    CART_HEADER = 0x0100,
    CART_ROM_0 = 0x0150,
    CART_ROM_X = 0x4000,
    CHARACTER_RAM = 0x8000,
    BG_MAP_1 = 0x9800,
    BG_MAP_2 = 0x9C00,
    CART_RAM = 0xA000,
    INT_RAM_0 = 0xC000,
    INT_RAM_X = 0xD000,
    ECHO_RAM = 0xE000,
    OAM = 0xFE00,
    RESERVED = 0xFEA0,
    HW_IO = 0xFF00,
    ZERO_PAGE = 0xFF80,
    IE_FLAG = 0xFFFF
} Section;


class Memory
{
public:
    Memory();

    void WriteByte(unsigned char data, unsigned short address);
    void WriteWord(unsigned short data, unsigned short address);

    unsigned char ReadByte(unsigned short address);
    unsigned short ReadWord(unsigned short address);

    void WriteToStack(unsigned short data);
    unsigned short ReadFromStack();

    void Copy(unsigned short destination, const unsigned char* source, const unsigned short length);
    void Memset(unsigned short destination, const unsigned char value, const unsigned short length);

    void Reset();
private:
    unsigned char _mem[0xFFFF];
};
