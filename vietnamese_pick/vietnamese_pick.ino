#include<Servo.h>
Servo pickServo;
#define dir1 5
#define dir2 6
#define switch1 2
#define switch2 3
#define pwm 4
#define servopin 9
int servoStart=0;
double defaultServoAng=90;
void setup() {
 Serial.begin(9600);
 pickServo.attach(9);
 pinMode(servopin,OUTPUT);
 pinMode(pwm,OUTPUT);
 pinMode(dir1,OUTPUT);
 pinMode(dir2,OUTPUT);

 pinMode(switch1,INPUT_PULLUP);
 pinMode(switch2,INPUT_PULLUP);
 analogWrite(pwm,100);
 
 pickServo.write(defaultServoAng);
 delay(20);
 
 attachInterrupt(digitalPinToInterrupt(switch1), actuate1,FALLING);
attachInterrupt(digitalPinToInterrupt(switch2), actuate2,FALLING);
}

void loop() {
    if(servoStart==1)
    {
     delay(5000);
     for(int i=defaultServoAng;i>=0;i--)
     {
       pickServo.write(i);
       delay(15);
     }
     servoStart=0;
    }
}
void actuate1()
{
  servoStart=1;
  digitalWrite( dir1,LOW);
  digitalWrite( dir2,HIGH);
}
void actuate2()
{ 
  servoStart=0;
  digitalWrite( dir1,HIGH);
  digitalWrite( dir2,LOW);
}


