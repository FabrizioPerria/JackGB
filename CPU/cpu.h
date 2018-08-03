#pragma once
#include <CPU/registers.h>
#include "Memory/memory.h"
#include "CPU/instructions.h"
#include <cstdio>
#include <QDebug>
#include <functional>

class CPU
{
public:
    CPU(Memory* memory);

    void Reset();
    void Step();

private:
    void writeToStack(unsigned short data);
    unsigned short readFromStack();

    unsigned long _ticks;
    unsigned char _stopped;

    Registers _registers;
    Memory* _memory;

    void undefined();
    void _xor(unsigned char value);
    void _dec(unsigned char value);

    void nop(); //0x00
    void ld_b_n(unsigned char operand);//0x06
    void ld_c_n(unsigned char operand);//0x0e
    void ld_hl_nn(unsigned short operand);// 0x21
    void ldd_hl_a();//0x32
    void xor_a(unsigned char operand);//0xaf

    void jump_nn(unsigned short operand);//0xc3

    const instruction instructions[256] = {
        { "NOP", 0, 2, {.executeVoid = &CPU::nop} },   // 0x00
        { "LD BC, <WORD>", 2, 6, {nullptr}},           // 0x01
        { "LD (BC), A", 0, 4, {nullptr} },               // 0x02
        { "INC BC", 0, 4, {nullptr} },                     // 0x03
        { "INC B", 0, 2, {nullptr} },                       // 0x04
        { "DEC B", 0, 2, {nullptr} },                       // 0x05
        { "LD B, <BYTE>", 1, 4, {.executeChar = &CPU::ld_b_n}  },               // 0x06
        { "RLCA", 0, 4, {nullptr} },                         // 0x07
        { "LD (<WORD>), SP", 2, 10, {nullptr} },         // 0x08
        { "ADD HL, BC", 0, 4, {nullptr} },              // 0x09
        { "LD A, (BC)", 0, 4, {nullptr} },               // 0x0a
        { "DEC BC", 0, 4, {nullptr} },                     // 0x0b
        { "INC C", 0, 2, {nullptr} },                       // 0x0c
        { "DEC C", 0, 2, {nullptr} },                       // 0x0d
        { "LD C, <BYTE>", 1, 4, {.executeChar = &CPU::ld_c_n} },               // 0x0e
        { "RRCA", 0, 4, {nullptr} },                         // 0x0f
        { "STOP", 1, 2, {nullptr} },                         // 0x10
        { "LD DE, <WORD>", 2, 6, {nullptr} },            // 0x11
        { "LD (DE), A", 0, 4, {nullptr} },               // 0x12
        { "INC DE", 0, 4, {nullptr} },                     // 0x13
        { "INC D", 0, 2, {nullptr} },                       // 0x14
        { "DEC D", 0, 2, {nullptr} },                       // 0x15
        { "LD D, <BYTE>", 1, 4, {nullptr} },               // 0x16
        { "RLA", 0, 4, {nullptr} },                           // 0x17
        { "JR <BYTE>", 1, 4, {nullptr} },                    // 0x18
        { "ADD HL, DE", 0, 4, {nullptr} },              // 0x19
        { "LD A, (DE)", 0, 4, {nullptr} },               // 0x1a
        { "DEC DE", 0, 4, {nullptr} },                     // 0x1b
        { "INC E", 0, 2, {nullptr} },                       // 0x1c
        { "DEC E", 0, 2, {nullptr} },                       // 0x1d
        { "LD E, <BYTE>", 1, 4, {nullptr} },               // 0x1e
        { "RRA", 0, 4, {nullptr} },                           // 0x1f
        { "JR NZ, <BYTE>", 1, 0, {nullptr} },             // 0x20
        { "LOAD HL, <MEM>", 2, 6, {.executeShort = &CPU::ld_hl_nn} },            // 0x21
        { "LDI (HL), A", 0, 4, {nullptr} },             // 0x22
        { "INC HL", 0, 4, {nullptr} },                     // 0x23
        { "INC H", 0, 2, {nullptr} },                       // 0x24
        { "DEC H", 0, 2, {nullptr} },                       // 0x25
        { "LD H, <BYTE>", 1, 4, {nullptr} },               // 0x26
        { "DAA", 0, 2, {nullptr} },                           // 0x27
        { "JR Z, <BYTE>", 1, 0, {nullptr} },               // 0x28
        { "ADD HL, HL", 0, 4, {nullptr} },              // 0x29
        { "LDI A, (HL)", 0, 4, {nullptr} },             // 0x2a
        { "DEC HL", 0, 4, {nullptr} },                     // 0x2b
        { "INC L", 0, 2, {nullptr} },                       // 0x2c
        { "DEC L", 0, 2, {nullptr} },                       // 0x2d
        { "LD L, <BYTE>", 1, 4, {nullptr} },               // 0x2e
        { "CPL", 0, 2, {nullptr} },                           // 0x2f
        { "JR NC, <BYTE>", 1, 4, {nullptr} },             // 0x30
        { "LD SP, <WORD>", 2, 6, {nullptr} },            // 0x31
        { "LDD (HL), A", 0, 4, {.executeVoid = &CPU::ldd_hl_a} },             // 0x32
        { "INC SP", 0, 4, {nullptr} },                     // 0x33
        { "INC (HL)", 0, 6, {nullptr} },                  // 0x34
        { "DEC (HL)", 0, 6, {nullptr} },                  // 0x35
        { "LD (HL), <BYTE>", 1, 6, {nullptr} },          // 0x36
        { "SCF", 0, 2, {nullptr} },                           // 0x37
        { "JR C, <BYTE>", 1, 0, {nullptr} },               // 0x38
        { "ADD HL, SP", 0, 4, {nullptr} },              // 0x39
        { "LDD A, (HL)", 0, 4, {nullptr} },             // 0x3a
        { "DEC SP", 0, 4, {nullptr} },                     // 0x3b
        { "INC A", 0, 2, {nullptr} },                       // 0x3c
        { "DEC A", 0, 2, {nullptr} },                       // 0x3d
        { "LD A, <BYTE>", 1, 4, {nullptr} },               // 0x3e
        { "CCF", 0, 2, {nullptr} },                           // 0x3f
        { "LD B, B", 0, 2, {nullptr} },                       // 0x40
        { "LD B, C", 0, 2, {nullptr} },                    // 0x41
        { "LD B, D", 0, 2, {nullptr} },                    // 0x42
        { "LD B, E", 0, 2, {nullptr} },                    // 0x43
        { "LD B, H", 0, 2, {nullptr} },                    // 0x44
        { "LD B, L", 0, 2, {nullptr} },                    // 0x45
        { "LD B, (HL)", 0, 4, {nullptr} },               // 0x46
        { "LD B, A", 0, 2, {nullptr} },                    // 0x47
        { "LD C, B", 0, 2, {nullptr} },                    // 0x48
        { "LD C, C", 0, 2, {nullptr} },                       // 0x49
        { "LD C, D", 0, 2, {nullptr} },                    // 0x4a
        { "LD C, E", 0, 2, {nullptr} },                    // 0x4b
        { "LD C, H", 0, 2, {nullptr} },                    // 0x4c
        { "LD C, L", 0, 2, {nullptr} },                    // 0x4d
        { "LD C, (HL)", 0, 4, {nullptr} },               // 0x4e
        { "LD C, A", 0, 2, {nullptr} },                    // 0x4f
        { "LD D, B", 0, 2, {nullptr} },                    // 0x50
        { "LD D, C", 0, 2, {nullptr} },                    // 0x51
        { "LD D, D", 0, 2, {nullptr} },                       // 0x52
        { "LD D, E", 0, 2, {nullptr} },                    // 0x53
        { "LD D, H", 0, 2, {nullptr} },                    // 0x54
        { "LD D, L", 0, 2, {nullptr} },                    // 0x55
        { "LD D, (HL)", 0, 4, {nullptr} },               // 0x56
        { "LD D, A", 0, 2, {nullptr} },                    // 0x57
        { "LD E, B", 0, 2, {nullptr} },                    // 0x58
        { "LD E, C", 0, 2, {nullptr} },                    // 0x59
        { "LD E, D", 0, 2, {nullptr} },                    // 0x5a
        { "LD E, E", 0, 2, {nullptr} },                       // 0x5b
        { "LD E, H", 0, 2, {nullptr} },                    // 0x5c
        { "LD E, L", 0, 2, {nullptr} },                    // 0x5d
        { "LD E, (HL)", 0, 4, {nullptr} },               // 0x5e
        { "LD E, A", 0, 2, {nullptr} },                    // 0x5f
        { "LD H, B", 0, 2, {nullptr} },                    // 0x60
        { "LD H, C", 0, 2, {nullptr} },                    // 0x61
        { "LD H, D", 0, 2, {nullptr} },                    // 0x62
        { "LD H, E", 0, 2, {nullptr} },                    // 0x63
        { "LD H, H", 0, 2, {nullptr} },                       // 0x64
        { "LD H, L", 0, 2, {nullptr} },                    // 0x65
        { "LD H, (HL)", 0, 4, {nullptr} },               // 0x66
        { "LD H, A", 0, 2, {nullptr} },                    // 0x67
        { "LD L, B", 0, 2, {nullptr} },                    // 0x68
        { "LD L, C", 0, 2, {nullptr} },                    // 0x69
        { "LD L, D", 0, 2, {nullptr} },                    // 0x6a
        { "LD L, E", 0, 2, {nullptr} },                    // 0x6b
        { "LD L, H", 0, 2, {nullptr} },                    // 0x6c
        { "LD L, L", 0, 2, {nullptr} },                       // 0x6d
        { "LD L, (HL)", 0, 4, {nullptr} },               // 0x6e
        { "LD L, A", 0, 2, {nullptr} },                    // 0x6f
        { "LD (HL), B", 0, 4, {nullptr} },               // 0x70
        { "LD (HL), C", 0, 4, {nullptr} },               // 0x71
        { "LD (HL), D", 0, 4, {nullptr} },               // 0x72
        { "LD (HL), E", 0, 4, {nullptr} },               // 0x73
        { "LD (HL), H", 0, 4, {nullptr} },               // 0x74
        { "LD (HL), L", 0, 4, {nullptr} },               // 0x75
        { "HALT", 0, 2, {nullptr} },                         // 0x76
        { "LD (HL), A", 0, 4, {nullptr} },               // 0x77
        { "LD A, B", 0, 2, {nullptr} },                    // 0x78
        { "LD A, C", 0, 2, {nullptr} },                    // 0x79
        { "LD A, D", 0, 2, {nullptr} },                    // 0x7a
        { "LD A, E", 0, 2, {nullptr} },                    // 0x7b
        { "LD A, H", 0, 2, {nullptr} },                    // 0x7c
        { "LD A, L", 0, 2, {nullptr} },                    // 0x7d
        { "LD A, (HL)", 0, 4, {nullptr} },               // 0x7e
        { "LD A, A", 0, 2, {nullptr} },                       // 0x7f
        { "ADD A, B", 0, 2, {nullptr} },                  // 0x80
        { "ADD A, C", 0, 2, {nullptr} },                  // 0x81
        { "ADD A, D", 0, 2, {nullptr} },                  // 0x82
        { "ADD A, E", 0, 2, {nullptr} },                  // 0x83
        { "ADD A, H", 0, 2, {nullptr} },                  // 0x84
        { "ADD A, L", 0, 2, {nullptr} },                  // 0x85
        { "ADD A, (HL)", 0, 4, {nullptr} },             // 0x86
        { "ADD A", 0, 2, {nullptr} },                     // 0x87
        { "ADC B", 0, 2, {nullptr} },                       // 0x88
        { "ADC C", 0, 2, {nullptr} },                       // 0x89
        { "ADC D", 0, 2, {nullptr} },                       // 0x8a
        { "ADC E", 0, 2, {nullptr} },                       // 0x8b
        { "ADC H", 0, 2, {nullptr} },                       // 0x8c
        { "ADC L", 0, 2, {nullptr} },                       // 0x8d
        { "ADC (HL)", 0, 4, {nullptr} },                  // 0x8e
        { "ADC A", 0, 2, {nullptr} },                       // 0x8f
        { "SUB B", 0, 2, {nullptr} },                       // 0x90
        { "SUB C", 0, 2, {nullptr} },                       // 0x91
        { "SUB D", 0, 2, {nullptr} },                       // 0x92
        { "SUB E", 0, 2, {nullptr} },                       // 0x93
        { "SUB H", 0, 2, {nullptr} },                       // 0x94
        { "SUB L", 0, 2, {nullptr} },                       // 0x95
        { "SUB (HL)", 0, 4, {nullptr} },                  // 0x96
        { "SUB A", 0, 2, {nullptr} },                       // 0x97
        { "SBC B", 0, 2, {nullptr} },                       // 0x98
        { "SBC C", 0, 2, {nullptr} },                       // 0x99
        { "SBC D", 0, 2, {nullptr} },                       // 0x9a
        { "SBC E", 0, 2, {nullptr} },                       // 0x9b
        { "SBC H", 0, 2, {nullptr} },                       // 0x9c
        { "SBC L", 0, 2, {nullptr} },                       // 0x9d
        { "SBC (HL)", 0, 4, {nullptr} },                  // 0x9e
        { "SBC A", 0, 2, {nullptr} },                       // 0x9f
        { "AND B", 0, 2, {nullptr} },                       // 0xa0
        { "AND C", 0, 2, {nullptr} },                       // 0xa1
        { "AND D", 0, 2, {nullptr} },                       // 0xa2
        { "AND E", 0, 2, {nullptr} },                       // 0xa3
        { "AND H", 0, 2, {nullptr} },                       // 0xa4
        { "AND L", 0, 2, {nullptr} },                       // 0xa5
        { "AND (HL)", 0, 4, {nullptr} },                  // 0xa6
        { "AND A", 0, 2, {nullptr} },                       // 0xa7
        { "XOR B", 0, 2, {nullptr} },                       // 0xa8
        { "XOR C", 0, 2, {nullptr} },                       // 0xa9
        { "XOR D", 0, 2, {nullptr} },                       // 0xaa
        { "XOR E", 0, 2, {nullptr} },                       // 0xab
        { "XOR H", 0, 2, {nullptr} },                       // 0xac
        { "XOR L", 0, 2, {nullptr} },                       // 0xad
        { "XOR (HL)", 0, 4, {nullptr} },                  // 0xae
        { "XOR A", 0, 2, {.executeChar = &CPU::xor_a} },                       // 0xaf
        { "OR B", 0, 2, {nullptr} },                         // 0xb0
        { "OR C", 0, 2, {nullptr} },                         // 0xb1
        { "OR D", 0, 2, {nullptr} },                         // 0xb2
        { "OR E", 0, 2, {nullptr} },                         // 0xb3
        { "OR H", 0, 2, {nullptr} },                         // 0xb4
        { "OR L", 0, 2, {nullptr} },                         // 0xb5
        { "OR (HL)", 0, 4, {nullptr} },                    // 0xb6
        { "OR A", 0, 2, {nullptr} },                         // 0xb7
        { "CP B", 0, 2, {nullptr} },                         // 0xb8
        { "CP C", 0, 2, {nullptr} },                         // 0xb9
        { "CP D", 0, 2, {nullptr} },                         // 0xba
        { "CP E", 0, 2, {nullptr} },                         // 0xbb
        { "CP H", 0, 2, {nullptr} },                         // 0xbc
        { "CP L", 0, 2, {nullptr} },                         // 0xbd
        { "CP (HL)", 0, 4, {nullptr} },                    // 0xbe
        { "CP A", 0, 2, {nullptr} },                         // 0xbf
        { "RET NZ", 0, 0, {nullptr} },                     // 0xc0
        { "POP BC", 0, 6, {nullptr} },                     // 0xc1
        { "JUMP NZ, <WORD>", 2, 0, {nullptr} },            // 0xc2
        { "JUMP <WORD>", 2, 6, {.executeShort = &CPU::jump_nn} }, // 0xc3
        { "CALL NZ, <WORD>", 2, 0, {nullptr} },        // 0xc4
        { "PUSH BC", 0, 8, {nullptr} },                   // 0xc5
        { "ADD A, <BYTE>", 1, 4, {nullptr} },             // 0xc6
        { "RST 0x00", 0, 8, {nullptr} },                    // 0xc7
        { "RET Z", 0, 0, {nullptr} },                       // 0xc8
        { "RET", 0, 2, {nullptr} },                           // 0xc9
        { "JP Z, <WORD>", 2, 0, {nullptr} },              // 0xca
        { "CB %02X", 1, 0, {nullptr} },                      // 0xcb
        { "CALL Z, <WORD>", 2, 0, {nullptr} },          // 0xcc
        { "CALL <WORD>", 2, 6, {nullptr} },               // 0xcd
        { "ADC <BYTE>", 1, 4, {nullptr} },                  // 0xce
        { "RST 0x08", 0, 8, {nullptr} },                   // 0xcf
        { "RET NC", 0, 0, {nullptr} },                     // 0xd0
        { "POP DE", 0, 6, {nullptr} },                     // 0xd1
        { "JP NC, <WORD>", 2, 0, {nullptr} },            // 0xd2
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xd3
        { "CALL NC, <WORD>", 2, 0, {nullptr} },        // 0xd4
        { "PUSH DE", 0, 8, {nullptr} },                   // 0xd5
        { "SUB <BYTE>", 1, 4, {nullptr} },                  // 0xd6
        { "RST 0x10", 0, 8, {nullptr} },                   // 0xd7
        { "RET C", 0, 0, {nullptr} },                       // 0xd8
        { "RETI", 0, 8, {nullptr} },          // 0xd9
        { "JP C, <WORD>", 2, 0, {nullptr} },              // 0xda
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xdb
        { "CALL C, <WORD>", 2, 0, {nullptr} },          // 0xdc
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xdd
        { "SBC <BYTE>", 1, 4, {nullptr} },                  // 0xde
        { "RST 0x18", 0, 8, {nullptr} },                   // 0xdf
        { "LD (0xFF00 + <BYTE>), A", 1, 6, {nullptr} },// 0xe0
        { "POP HL", 0, 6, {nullptr} },                     // 0xe1
        { "LD (0xFF00 + C), A", 0, 4, {nullptr} },      // 0xe2
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xe3
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xe4
        { "PUSH HL", 0, 8, {nullptr} },                   // 0xe5
        { "AND <BYTE>", 1, 4, {nullptr} },                  // 0xe6
        { "RST 0x20", 0, 8, {nullptr} },                   // 0xe7
        { "ADD SP,<BYTE>", 1, 8, {nullptr} },            // 0xe8
        { "JP HL", 0, 2, {nullptr} },                       // 0xe9
        { "LD (<WORD>), A", 2, 8, {nullptr} },           // 0xea
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xeb
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xec
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xed
        { "XOR <BYTE>", 1, 4, {nullptr} },                  // 0xee
        { "RST 0x28", 0, 8, {nullptr} },                   // 0xef
        { "LD A, (0xFF00 + <BYTE>)", 1, 6, {nullptr} },// 0xf0
        { "POP AF", 0, 6, {nullptr} },                     // 0xf1
        { "LD A, (0xFF00 + C)", 0, 4, {nullptr} },      // 0xf2
        { "DI", 0, 2, {nullptr} },                        // 0xf3
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xf4
        { "PUSH AF", 0, 8, {nullptr} },                   // 0xf5
        { "OR <BYTE>", 1, 4, {nullptr} },                    // 0xf6
        { "RST 0x30", 0, 8, {nullptr} },                   // 0xf7
        { "LD HL, SP+<BYTE>", 1, 6, {nullptr} },       // 0xf8
        { "LD SP, HL", 0, 4, {nullptr} },                // 0xf9
        { "LD A, (<WORD>)", 2, 8, {nullptr} },           // 0xfa
        { "EI", 0, 2, {nullptr} },                             // 0xfb
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xfc
        { "UNKNOWN", 0, 0, {nullptr} },                 // 0xfd
        { "CP <BYTE>", 1, 4, {nullptr} },                    // 0xfe
        { "RST 0x38", 0, 8, {nullptr} },                   // 0xff
    };
};











//

/*
 * set all RAM to value $00 on entry
 * read from cartridge $104 to $133 and place this graphic of a Nintendo logo on the screen at the top
 *  Two musical notes are then played on the
 internal speaker. Again, the cartridge locations $104
 to $133 are read but this time they are compared with
 a table in the internal rom.
 If any byte fails to compare, then the GameBoy stops
 comparing bytes and simply halts all operations

*/



