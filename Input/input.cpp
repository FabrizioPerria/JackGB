#include "input.h"
#include <cstring>

Input::Input()
{
}

char Input::Step()
{
    return 1;
}

void Input::Reset()
{
    memset(_keys, 1, 8);
}
