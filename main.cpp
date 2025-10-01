#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <qlogging.h>
#include <qobject.h>
#include <string>
#include <synchapi.h>

int main( int argc, char *argv[] )
{
    // QApplication a( argc, argv );
    // MainWindow w;
    uart ard( "COM5" );
    Sleep( 100 );
    std::string data {};
    while ( 1 )
    {
        data = "H W!!\n";
        ard.writeLine( data );
        data.clear();
        ard.readLine( data );
        if ( data.size() )
        {
            auto d = QString( data.data() );
            data.clear();
        }
        // data.clear();
    }
    // w.show();
    // return a.exec();
}
