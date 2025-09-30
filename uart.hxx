#include <Windows.h>
#include <cassert>
#include <handleapi.h>
#include <minwindef.h>
#include <string>
#include <iostream>

class uart
{
    HANDLE hComm;

  public:
    uart( const char *port )
    {
        hComm = CreateFileA( port,                  // port name
                             GENERIC_WRITE,         // Read/Write
                             0,                     // No Sharing
                             NULL,                  // No Security
                             OPEN_EXISTING,         // Open existing port only
                             FILE_ATTRIBUTE_NORMAL, // Non Overlapped I/O
                             NULL );

        if ( hComm == INVALID_HANDLE_VALUE )
        {
            std::cerr << "Error in opening serial port”";
        }
        else
            std::cerr << "opening serial port successful";
    }
    ~uart()
    {
        CloseHandle( hComm );
    }

    void readLine( std::string &buffer )
    {
        char ch;
        DWORD readedBytes { 0 };
        while ( ReadFile( hComm, &ch, 1, &readedBytes, NULL ) && readedBytes > 0 )
        {
            if ( ch == '\n' )
            {
                break; // Конец строки
            }
            if ( ch != '\r' )
            { // Пропускаем carriage return
                buffer += ch;
            }
        }
    }

    void writeLine( std::string &buffer )
    {
        DWORD writenBytes { 0 };
        while ( !writenBytes )
        {
            WriteFile( hComm,                                 // Handle to the Serial port
                       buffer.data(),                         // Data to be written to the port
                       sizeof( buffer[ 0 ] ) * buffer.size(), // No of bytes to write
                       &writenBytes,                          // Bytes written
                       NULL );
        }
    }
};