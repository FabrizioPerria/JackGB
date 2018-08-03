#pragma once

enum Key
{
    A,
    B,
    START,
    SELECT,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Input
{
public:
    Input();
    char Step();
    void Reset();

private:
    unsigned char _keys[8];
};
