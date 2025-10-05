#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio( 7, 53 ); // CE, CSN

const uint64_t address[ 2 ] = { 0xE8E8F0F0E1LL, 0xE8E8F0F0E2LL };
// char data[ 4 ] { };

void setup()
{
    Serial.begin( 9600 );
    pinMode( LED_BUILTIN, OUTPUT );
    radio.begin();
    // radio.openReadingPipe( 1, address[ 1 ] );
    radio.setPayloadSize( 3 );
    radio.setChannel( 19 );
    radio.setPALevel( RF24_PA_HIGH );
    radio.setDataRate( RF24_1MBPS );
    radio.setAutoAck( 0 );
    radio.openWritingPipe( address[ 0 ] );
    radio.stopListening();
    // radio.enableDynamicPayloads();
    // radio.setRetries(5, 15); // 5 повторов с задержкой 1500 мкс
    // radio.flush_tx();
    // radio.writeAckPayload( 1, data, 3 );
}
uint8_t ch;
uint8_t data[4] = {};
void loop()
{
    // digitalWrite( LED_BUILTIN, 0 );
    if ( Serial.available() )
    // data[1] = 10;
    {
        ch = Serial.readBytes(data, 4);
        if ( radio.write( data, 3 ) )
        {
            digitalWrite( LED_BUILTIN, 1 );
            // radio.startListening();
            // radio.openReadingPipe( 1, address[ 1 ] );
            // delay(1);
            // if ( radio.available() )
            // {
                // int i = radio.getDynamicPayloadSize();
                // char *d = new char[i+1];
                // d[i] = '\0';
                // radio.read( data, 3 );
                // delete[] d;
            //}
        }
        // }
    }
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}