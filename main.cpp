#include "mainwindow.h"
#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    uart ard( "COM5" );
    MainWindow w { ard };
    w.show();
    return a.exec();
}
