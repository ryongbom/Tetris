#include <QApplication>
#include "tetrisgame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TetrisGame game;
    game.show();

    return a.exec();
}
