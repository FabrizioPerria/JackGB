#include "CPU/cpu.h"
#include "CPU/instructions.h"
#include "CPU/flags.h"

/*
    Terminology
    b	A bit number in any 8-bit register or memory location.
    C	Carry flag.
    cc	Flag condition code: C,NC,NZ,Z
    d	Any 8-bit destination register or memory location.
    dd	Any 16-bit destination register or memory location.
    e	8-bit signed 2's complement displacement.
    f	8 special call locations in page zero.
    H	Half-carry flag.
    N	Subtraction flag.
    NC	Not carry flag
    NZ	Not zero flag.
    n	Any 8-bit binary number.
    nn	Any 16-bit binary number.
    r	Any 8-bit register. (A,B,C,D,E,H, or L)
    s	Any 8-bit source register or memory location.
    sb	A bit in a specific 8-bit register or memory location.
    ss	Any 16-bit source register or memory location.
    Z	Zero Flag.
*/

void CPU::undefined()
{
    _registers.pc--;

    unsigned char instruction = _memory->ReadByte(_registers.pc);
    qDebug() << instructions[instruction].instruction << "undefined";
    exit(-1);
}

void CPU::_xor(unsigned char value)
{
    _registers.a ^= data;

    if(_registers.a) FLAGS_CLEAR(FLAGS_ZERO);
    else FLAGS_SET(FLAGS_ZERO);

    FLAGS_CLEAR(FLAGS_CARRY | FLAGS_HALFCARRY | FLAGS_NEGATIVE);
}

void CPU::_dec(unsigned char value)
{

}

void CPU::nop() { }

void CPU::ld_b_n(unsigned char operand) { _registers.b = operand; }

void CPU::ld_c_n(unsigned char operand) { _registers.c = operand; }

void CPU::ld_hl_nn(unsigned short operand) { _registers.hl = operand; }

void CPU::ldd_hl_a() { _memory->WriteByte(_registers.hl, _registers.a); _registers.hl--; }

void CPU::xor_a(unsigned char operand) { _xor(_registers.a); }

void CPU::jump_nn(unsigned short operand) { _registers.pc = operand; }


