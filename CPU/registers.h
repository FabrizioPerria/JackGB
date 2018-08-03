#pragma once

struct Registers
{
    struct {
        union {
            struct {
                unsigned char f;
                unsigned char a;
            };
            unsigned af;
        };

        union {
            struct {
                unsigned char c;
                unsigned char b;
            };
            unsigned bc;
        };

        union {
            struct {
                unsigned char e;
                unsigned char d;
            };
            unsigned de;
        };

        union {
            struct {
                unsigned char l;
                unsigned char h;
            };
            unsigned hl;
        };
    };

    unsigned short sp;
    unsigned short pc;
};
