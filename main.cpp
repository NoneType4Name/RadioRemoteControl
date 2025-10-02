#include "mainwindow.h"
#include <QApplication>
#include <synchapi.h>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    uart ard( "COM5" );
    Sleep( 100 );
    MainWindow w { ard };
    // Sleep( 100 );
    // std::string data {};
    // while ( 1 )
    // {
    //     data = "H W!!\n";
    //     ard.writeLine( data );
    //     data.clear();
    //     ard.readLine( data );
    //     if ( data.size() )
    //     {
    //         std::cout << data.data() << '\n';
    //         data.clear();
    //     }
    //     data.clear();
    // }
    w.show();
    return a.exec();
}
