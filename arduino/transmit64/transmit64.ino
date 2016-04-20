// this sketch accepts bytes via a Serial connection
// and writes them to the output pin 1. 
// pin 0 serves a clock signal
// data is written pin 1 if pin 0 is at HIGH
// a LED at pin 13 shows

#define BAUD_RATE 9600
#define LED_PIN 13

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop()
{
  readSerial();
}

bool readSerial()
{
  while (Serial.available() > 0) 
  {
    byte data = Serial.read();
  }
}

