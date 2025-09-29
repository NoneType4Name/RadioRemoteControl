#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>
#include <iostream>
#include <qobject.h>
#include <winnt.h>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    HANDLE hComm;
    std::string port_name = "COM3"; // change port name
    DWORD dNoOFBytestoWrite;        // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;    // No of bytes written to the port
    DWORD bytes_read        = 0;
    uint8_t wtireBuffer { 0 };

    hComm = CreateFileA( port_name.c_str(),     // port name
                         GENERIC_WRITE,         // Read/Write
                         0,                     // No Sharing
                         NULL,                  // No Security
                         OPEN_EXISTING,         // Open existing port only
                         FILE_ATTRIBUTE_NORMAL, // Non Overlapped I/O
                         NULL );                // Null for Comm Devices

    if ( hComm == INVALID_HANDLE_VALUE )
    {
        std::cerr << "Error in opening serial port”";
        return -1;
    }
    else
        std::cerr << "opening serial port successful";

    DCB dcbSerialParams       = { 0 }; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof( dcbSerialParams );
    GetCommState( hComm, &dcbSerialParams );

    dcbSerialParams.BaudRate = CBR_9600;   // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;          // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
    dcbSerialParams.Parity   = NOPARITY;   // Setting Parity = None
    SetCommState( hComm, &dcbSerialParams );

    COMMTIMEOUTS timeouts                = { 0 };
    timeouts.ReadIntervalTimeout         = 20;  // in milliseconds
    timeouts.ReadTotalTimeoutConstant    = 100; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier  = 10;  // in milliseconds
    timeouts.WriteTotalTimeoutConstant   = 100; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 10;  // in milliseconds

    while ( 1 )
    {
        if ( !dNoOfBytesWritten )
        {
            WriteFile( hComm,                 // Handle to the Serial port
                       &wtireBuffer,          // Data to be written to the port
                       sizeof( wtireBuffer ), // No of bytes to write
                       &dNoOfBytesWritten,    // Bytes written
                       NULL );
            dNoOfBytesWritten = 0;
            if ( wtireBuffer < 255 )
                ++wtireBuffer;
            else
                wtireBuffer = 0;
        }
    }
    // while (1) {
    //   ReadFile(hComm,              // Handle of the Serial port
    //            read_buffer.data(), // Temporary character
    //            1,                  // Size of TempChar
    //            &bytes_read,        // Number of bytes read
    //            NULL);
    //   if (bytes_read > 0) {
    //     std::cout << read_buffer.data();
    //     read_buffer.clear();
    //   }
    // }

    CloseHandle( hComm ); // Closing the Serial Port
    MainWindow w;
    w.show();
    return a.exec();
}
