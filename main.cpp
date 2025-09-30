// #include "mainwindow.h"
// #include <QApplication>
#include <iostream>
#include "uart.hxx"
// #include <qobject.h>
#include <string>

int main( int argc, char *argv[] )
{
    // QApplication a( argc, argv );
    // MainWindow w;
    uart ard( "COM5" );
    std::string data {};
    while ( 1 )
    {
        ard.readLine( data );
        if ( !data.empty() )
            std::cout << data.size() << std::endl;
        // data.clear();
    }
    // w.show();
    // return a.exec();
}
