#include <QApplication>
#include <QDebug>
#include "gameboy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argc != 2)
    {
        qDebug() << "No ROM to open!";
        return -1;
    }

    GameBoy gameboy;
    gameboy.Play(argv[1]);

    return a.exec();

}
