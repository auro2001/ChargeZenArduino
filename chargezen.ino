#include <SoftwareSerial.h> 
SoftwareSerial bluetooth(10, 11); // TX,RX
int relay=9;
int led=12;
int buzz=13;
int val;
int tempPin = 3;
const int analogPin = A1;
float analogValue;
float input_voltage;
int latchPin = 6;//ST
int clockPin = 5;//SH
int dataPin = 7;//DS 

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(relay, OUTPUT); 
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  //pinMode(relay,HIGH);
  
}

void updateShiftRegister(byte storageByte)
{
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, storageByte);

  digitalWrite(latchPin, HIGH);
}

void temp()
{
  val = analogRead(tempPin);
  float mv = (val/1024.0)*3000;
  float cel = mv/10;
  delay(1000);
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
}

void bluetoot()
{
  while(!bluetooth.available());
    char value = bluetooth.read();
    switch(value)
    {
      case 'O':
        digitalWrite(relay,LOW);
        break;
      case 'F':
        digitalWrite(relay,HIGH);
        break;
    }
}

void loop()
{
   digitalWrite(relay,HIGH);
   analogValue = analogRead (A1);
   Serial.println(analogValue);
   delay (1000); 
   input_voltage = (analogValue*9) / 1023.0;
   Serial.println("Voltage= ");
   Serial.println(input_voltage);
   delay(1000);
  
  if (input_voltage < 2.50 && input_voltage >= 0.00 )
  { 
    byte storageByte = 0x80; 
    updateShiftRegister(storageByte);
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    Serial.println("Drain");
    Serial.println("Health:Bad");
    temp();
    Serial.println("Percentage: 0");
    digitalWrite(relay,LOW);
    delay(3000);
    Serial.println("On");
    void bluetoot();
  } 
  else if (input_voltage < 2.70 && input_voltage >=2.50 )
  {
    byte storageByte = 0xC0;
    updateShiftRegister(storageByte);
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    temp();
    Serial.println("Percentage: 20");
    Serial.println("Health:Bad");
    Serial.println("On");
    Serial.println("Drain");
    
    
  }   
  else if (input_voltage < 3.00 && input_voltage >=2.75 )
  {
    byte storageByte = 0xE0;
    updateShiftRegister(storageByte);
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    digitalWrite(relay,LOW);
    delay(1000);
    Serial.println("Percentage: 40");
    Serial.println("Health:Bad");
    temp();
    Serial.println("On");
    Serial.println("Drain");
    
  }
  else if (input_voltage < 3.25 && input_voltage >= 3.00)
  {
    byte storageByte = 0xF0;
    updateShiftRegister(storageByte);
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    digitalWrite(relay,LOW);
    delay(1000);
    Serial.println("Percentage: 60");
    temp();
    Serial.println("Health:Bad");
    Serial.println("On");
    Serial.println("Drain");
    
  }
  else if (input_voltage < 3.50 && input_voltage >= 3.25)
  {
    byte storageByte = 0xF8;
    updateShiftRegister(storageByte);
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    /*digitalWrite(relay,LOW);
    delay(1000);*/
    Serial.println("Percentage: 70");
    Serial.println("Health:Bad");
    temp();
    Serial.println("On");
    Serial.println("Drain");
    
  }
  else if (input_voltage <3.70 && input_voltage >= 3.50)
  {
    byte storageByte = 0xFC;
    updateShiftRegister(storageByte);
    Serial.println("Percentage: 80");
    Serial.println("Health:Bad");
    temp();
    
  }
  else if (input_voltage < 3.83 && input_voltage >= 3.70)
  {
    byte storageByte = 0xFE;
    updateShiftRegister(storageByte);
    Serial.println("Percentage: 90");
    Serial.println("Health:Good");
    temp();
  }
  else if (input_voltage <= 5.00 && input_voltage >= 3.85)
  {
    byte storageByte = 0xFF;
    updateShiftRegister(storageByte);
    for(int k=0;k<2;k++)
    {    
      Serial.println("Full");
    }
    digitalWrite(buzz, HIGH);
    delay(3000);
    digitalWrite(buzz, LOW);
    delay (1000);
    digitalWrite(led, HIGH);
    delay (5000);
    digitalWrite(led, LOW);
    delay (1000);
    //digitalWrite(relay,HIGH);
    //delay(3000);
    Serial.println("Percentage: 95");
    temp();
    Serial.println("Health:Good");
    Serial.println("OFF");
    void bluetoot(); 
   } 
}
