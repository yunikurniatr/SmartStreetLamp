#include <Arduino.h>

const int lamp1 = D0;
const int lamp2 = D1;
const int lamp3 = D2;
const int ldrPin = A0;
void setup()
{

  Serial.begin(115200);

  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(lamp3, OUTPUT);

  pinMode(ldrPin, INPUT);
}
void loop()
{
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus < 650)
  {
    digitalWrite(lamp1, HIGH);
    digitalWrite(lamp2, HIGH);
    digitalWrite(lamp3, HIGH);
  }
  else
  {
    digitalWrite(lamp1, LOW);
    digitalWrite(lamp2, LOW);
    digitalWrite(lamp3, LOW);
  }
  //checking value
  Serial.println(ldrStatus);
  delay(500);
}