// this sketch accepts bytes via a Serial connection
// and writes them to the output pin 1.
// pin 0 serves a clock signal
// data is written pin 1 if pin 0 is at HIGH
// a LED at pin 13 shows

#define BAUD_RATE 9600
#define LED_PIN 13
#define CLOCK_PIN 10
#define DATA_PIN 11
#define CLOCK_DELAY 100

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);
  
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
    writeToC64(buf);
    Serial.print("o");
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

void writeToC64(byte input)
{
  for( int i = 0; i < 8; i++ )
  {
    bool bitIsSet = (input >> i) & 0x1;
    writeBit(bitIsSet);
  }
}

void writeBit(bool value)
{
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  delay(CLOCK_DELAY);
  
  digitalWrite(DATA_PIN, value ? HIGH : LOW);
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(CLOCK_DELAY);
}



