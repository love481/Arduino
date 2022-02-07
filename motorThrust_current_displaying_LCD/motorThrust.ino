
// include the library code:
#include <LiquidCrystal.h>
#include "HX711.h"
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;
const int currentSensor=A4;
const int motorPot=A5;
const int motorPwm=10;
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
int sensitivity = 66;
double adcVoltage= 0;
int offsetVoltage = 2500;
double currentValue=0;
double pwmValue;
double reading=0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
HX711 scale;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(38400);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(motorPwm,OUTPUT);
  scale.set_scale(390.f);              
  scale.tare();      
}

void loop() {
  //handle motor rotation based on potentiometer rotation
  pwmValue=map(analogRead(motorPot),0,1024,1000,2000);
  if(pwmValue>1050)
   {digitalWrite(motorPwm,HIGH);
    delayMicroseconds(pwmValue);
    digitalWrite(motorPwm,LOW);
    delayMicroseconds(pwmValue);
   }
  //Handles current sensor readings
  adcVoltage = (analogRead(currentSensor) / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  if(!isnan(currentValue))
   {
    lcd.setCursor(0,1);
   lcd.print(currentValue-10.7,3);
   lcd.setCursor(8,1);
   lcd.print('A');
   }
   if(scale.is_ready()) 
    {lcd.setCursor(0,0);
    reading = scale.get_units();
    lcd.print(reading,3);
    lcd.setCursor(7,0);
    lcd.print('g');}
    Serial.println(reading);
  //delay(1000);
  
}
