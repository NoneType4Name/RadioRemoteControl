#include <Windows.h>
#include <string>
#include <QString>
#include <iostream>

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

        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity   = NOPARITY;
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
        Sleep( 1000 );
    }
    ~uart()
    {
        CloseHandle( hComm );
    }

    template<typename _T_str>
    void readLine( _T_str &buffer )
    {
        char ch;
        DWORD readedBytes { 0 };
        while ( ReadFile( hComm, &ch, 1, &readedBytes, NULL ) && readedBytes > 0 )
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

    void writeLine( const uint8_t *d, size_t s )
    {
        DWORD writenBytes { 0 };
        // buffer += '\n';
        while ( !writenBytes )
        {
            WriteFile( hComm,
                       d, s,
                       &writenBytes,
                       NULL );
        }
    }
};