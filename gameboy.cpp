#include "gameboy.h"
#include "ROM/rom.h"

GameBoy::GameBoy()
{
    _memory = new Memory();
    _cpu = new CPU(_memory);
    _pic = new PIC();
    _input = new Input();
    _display = new Display();
}

void GameBoy::InsertCartridge(const char* game)
{
    ROM::loadROMToMemory(game, _memory);
}

GameBoy::~GameBoy()
{
    delete _display;
    delete _input;
    delete _pic;
    delete _cpu;
    delete _memory;
}

void GameBoy::Play(const char* game)
{
    Reset();
    InsertCartridge(game);
    GameLoop();
}

void GameBoy::Reset()
{
    _memory->Reset();
    _cpu->Reset();
    _pic->Reset();
    _input->Reset();
    _display->Reset();
    //_gpu->Reset();
}

void GameBoy::GameLoop()
{
    while(_input->Step())
    {
        _cpu->Step();
        //GpuStep();
        _pic->Step();
    }
}
