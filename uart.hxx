#include <Windows.h>
#include <cassert>
#include <handleapi.h>
#include <minwindef.h>
#include <string>
#include <iostream>
#include <winnt.h>

class uart
{
    HANDLE hComm;

  public:
    uart( const char *port )
    {
        hComm = CreateFileA( port,                         // port name
                             GENERIC_WRITE | GENERIC_READ, // Read/Write
                             0,                            // No Sharing
                             NULL,                         // No Security
                             OPEN_EXISTING,                // Open existing port only
                             FILE_ATTRIBUTE_NORMAL,        // Non Overlapped I/O
                             NULL );

        if ( hComm == INVALID_HANDLE_VALUE )
        {
            std::cerr << "Error in opening serial port";
        }
        else
            std::cerr << "opening serial port successful";

        DCB dcbSerialParams       = { 0 };
        dcbSerialParams.DCBlength = sizeof( dcbSerialParams );
        GetCommState( hComm, &dcbSerialParams );

        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity   = NOPARITY;
        SetCommState( hComm, &dcbSerialParams );

        COMMTIMEOUTS timeouts                = { 0 };
        timeouts.ReadIntervalTimeout         = 20;
        timeouts.ReadTotalTimeoutConstant    = 100;
        timeouts.ReadTotalTimeoutMultiplier  = 10;
        timeouts.WriteTotalTimeoutConstant   = 100;
        timeouts.WriteTotalTimeoutMultiplier = 10;
        if ( !SetCommTimeouts( hComm, &timeouts ) )
        {
            std::cerr << "Error setting timeouts" << std::endl;
        }
    }
    ~uart()
    {
        CloseHandle( hComm );
    }

    void readLine( std::string &buffer )
    {
        char ch;
        DWORD readedBytes { 0 };
        while ( ReadFile( hComm, &ch, sizeof( ch ), &readedBytes, NULL ) && readedBytes > 0 )
        {
            if ( ch == '\n' )
            {
                break;
            }
            if ( ch != '\r' )
            {
                buffer += ch;
            }
        }
    }

    void writeLine( std::string &buffer )
    {
        DWORD writenBytes { 0 };
        while ( !writenBytes )
        {
            WriteFile( hComm,
                       buffer.data(),
                       sizeof( buffer[ 0 ] ) * buffer.size(),
                       &writenBytes,
                       NULL );
        }
    }
};