#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio( 7, 53 ); // CE, CSN

const uint64_t address[ 2 ] = { 0xE8E8F0F0E1LL, 0xE8E8F0F0E2LL };

void setup()
{
    Serial.begin( 9600 );
    pinMode( LED_BUILTIN, OUTPUT );
    radio.begin();
    radio.setAutoAck(false);
    radio.openWritingPipe( address[ 0 ] );
    radio.openReadingPipe( 1, address[ 1 ] );
    radio.setChannel( 19 );
    radio.setPayloadSize( 13 );
    radio.setPALevel( RF24_PA_HIGH );
    radio.setDataRate( RF24_250KBPS );
    radio.startListening();
}

// String data;
char data[14]{};
String str;

void loop()
{
    int i = radio.available();
    digitalWrite(LED_BUILTIN, 0);
    if ( i )
    {
      digitalWrite(LED_BUILTIN, 1);
        // data.reserve( 13 );
        radio.read( data, 13 );
        data[13] = '\0';
        Serial.println( data );
    }
    if ( Serial.available() )
    {
        char d = Serial.read();
        if ( d != '\n' )
        {
            str += d;
        }
        // else
        // {
        //     if ( str[ 0 ] == 'p' )
        //     {
        //         analogWrite( LED_BUILTIN, map( str[ 1 ], -128, 127, 0, 255 ) );
        //     }
        //     str = "";
        // }
    }
}
