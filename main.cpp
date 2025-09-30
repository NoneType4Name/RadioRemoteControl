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
    uart ard( "COM3" );
    std::string data {};
    while ( 1 )
    {
        data = "H W!!";
        ard.writeLine( data );
        data.clear();
        ard.readLine( data );
        if ( !data.empty() )
        {
            std::cout << data.data() << std::endl;
            data.clear();
        }
        // data.clear();
    }
    // w.show();
    // return a.exec();
}
