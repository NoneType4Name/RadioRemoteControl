void setup()
{
    Serial.begin( 9600 );
    pinMode(LED_BUILTIN, OUTPUT);
}
String str = "";

void loop()
{
    if ( Serial.available() )
    {
        char data = Serial.read();
        if ( data != '\n' )
        {
            str += data;
        }
        else
        {
            if(str[0] == 'p')
            {
                analogWrite(LED_BUILTIN, map(str[1], -128, 127, 0, 255));
            }
            Serial.println(str[1]);
            str = "";
        }
    }
}