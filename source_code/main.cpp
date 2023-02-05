#include <QApplication>

#include "viwe/view_game.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  InSearchOfTreasure::ViewGame w;
  w.show();
  return a.exec();
}
