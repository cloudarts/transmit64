// this sketch accepts bytes via a Serial connection
// and writes them to the output pin 1.
// pin 0 serves a clock signal
// data is written pin 1 if pin 0 is at HIGH
// a LED at pin 13 shows

#define BAUD_RATE 9600
#define LED_PIN 13

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUD_RATE);
  
  // inform PC that we're waiting
  Serial.print("o");
}

void loop()
{
  readSerial();
}

bool readSerial()
{
  while (Serial.available() > 0)
  {
    byte buf;
    Serial.readBytes(&buf, 1);
    if ( buf == 97 )
    {
      //blink(2, 500);
      Serial.print("o");
    }
    else
    {
      Serial.print(byteToString(buf));
      //blink(3, 1000);
    }
  }
}

void blink(int num, int ms)
{
  for ( int i = 0; i < num; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(ms);
    digitalWrite(LED_PIN, LOW);
    delay(ms);
  }
}

String byteToString(const byte& input)
{
  String ret = "";
  for( int i = 7; i >= 0; i-- )
  {
    bool bitIsSet = (input >> i) & 0x1;
    ret += bitIsSet ? "1" : "0";
  }

  return ret;
}


