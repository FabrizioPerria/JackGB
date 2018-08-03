#pragma once

#include "Memory/memory.h"
#include "CPU/interrupts.h"
#include "Input/input.h"
#include "Rendering/display.h"
#include "CPU/cpu.h"

class GameBoy
{
public:
    GameBoy();
    ~GameBoy();

    void Play(const char* game);

private:
    CPU* _cpu;
    Memory* _memory;
    PIC* _pic;
    Input* _input;
    Display* _display;

    void Reset();
    void InsertCartridge(const char* game);
    void GameLoop();
};
