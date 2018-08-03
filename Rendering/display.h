#pragma once
#include "Rendering/glwindow.h"

typedef struct rgb {
    unsigned char r, g, b;
} Color;

const Color palette[4] = {
    { 255, 255, 255 },
    { 192, 192, 192 },
    { 96, 96, 96 },
    { 0, 0, 0 },
};

class Display
{
public:
    Display();

    void Reset();
    void Render();

private:
    GLWindow* _window;

    Color _framebuffer[160*144];

    unsigned char _dirtyTileSet;
};

