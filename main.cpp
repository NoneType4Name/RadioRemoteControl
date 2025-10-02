#include "mainwindow.h"
#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    uart ard( "COM3" );
    Sleep( 100 );
    MainWindow w { ard };
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
