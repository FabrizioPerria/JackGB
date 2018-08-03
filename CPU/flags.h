#pragma once

#define FLAGS_ZERO (1 << 7)
#define FLAGS_NEGATIVE (1 << 6)
#define FLAGS_HALFCARRY (1 << 5)
#define FLAGS_CARRY (1 << 4)

#define FLAGS_ISZERO (_registers.f & FLAGS_ZERO)
#define FLAGS_ISNEGATIVE (_registers.f & FLAGS_NEGATIVE)
#define FLAGS_ISCARRY (_registers.f & FLAGS_CARRY)
#define FLAGS_ISHALFCARRY (_registers.f & FLAGS_HALFCARRY)

#define FLAGS_ISSET(x) (_registers.f & (x))
#define FLAGS_SET(x) (_registers.f |= (x))
#define FLAGS_CLEAR(x) (_registers.f &= ~(x))
