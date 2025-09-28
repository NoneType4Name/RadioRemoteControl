#include "mainwindow.h"

#include <QApplication>
#include <qobject.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  QString sd{"1213232asd"};
  return a.exec();
}
