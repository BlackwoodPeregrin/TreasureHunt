#include "view_game.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nightmare::ViewGame w;
    w.show();
    return a.exec();
}
