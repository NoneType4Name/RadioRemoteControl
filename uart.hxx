#include <Windows.h>
#include <cassert>
#include <errhandlingapi.h>
#include <handleapi.h>
#include <minwindef.h>
#include <string>
#include <iostream>
#include <winbase.h>
#include <winnt.h>

class uart
{
    HANDLE hComm;

  public:
    uart( const char *port )
    {
        hComm = CreateFileA( port,                         // port name
                             GENERIC_READ | GENERIC_WRITE, // Read/Write
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

        dcbSerialParams.BaudRate        = CBR_9600;
        dcbSerialParams.ByteSize        = 8;
        dcbSerialParams.StopBits        = ONESTOPBIT;
        dcbSerialParams.Parity          = NOPARITY;
        dcbSerialParams.fDsrSensitivity = DTR_CONTROL_ENABLE;
        dcbSerialParams.fRtsControl     = RTS_CONTROL_ENABLE;
        SetCommState( hComm, &dcbSerialParams );

        COMMTIMEOUTS timeouts                = { 0 };
        timeouts.ReadIntervalTimeout         = 50;
        timeouts.ReadTotalTimeoutConstant    = 50;
        timeouts.ReadTotalTimeoutMultiplier  = 10;
        timeouts.WriteTotalTimeoutConstant   = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;
        if ( !SetCommTimeouts( hComm, &timeouts ) )
        {
            std::cerr << "Error setting timeouts" << std::endl;
        }
        // PurgeComm( hComm, PURGE_RXCLEAR | PURGE_TXCLEAR );
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
                       //    buffer.data(),
                       //    buffer.size(),
                       buffer.c_str(), buffer.size() + 1,
                       &writenBytes,
                       NULL );
        }
    }
};