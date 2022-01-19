/*Author:Love panta
 * 
 * created:16/6/2020
 */
#include"I2Cdev.h"
#include"Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 acgy;
uint16_t ax,ay,az;
uint16_t gx,gy,gz;
int pin_a1=4;
int pin_a2=5;
int pin_b1=6;
int pin_b2=7;
int accPitch,accRoll;
int setpoint;
uint32_t Time=0;
double gyroYvalue=0;
float gyroYrate=0;
double combineread;
int Max=255;
int Min=-255;
double Iterm=0;
double kp=60;
double ki=20;
double kd=0.8;
double lastinput=0;
float previoustime=0;
float dt=0;
double output;
void setup() {
  Wire.begin();
  Serial.begin(115200);
  acgy.initialize();
  Serial.print(acgy.testConnection()?"connection Successfull":"doesnot connected");
  pinMode(pin_a1,OUTPUT);
  pinMode(pin_a2,OUTPUT);
  pinMode(pin_b1,OUTPUT);
  pinMode(pin_b2,OUTPUT);
   acgy.calibrateGyro();
    acgy.setThreshold(3);
   acgy.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
   accPitch = atan2(-ay,az) * RAD_TO_DEG;
   setpoint=accPitch;
    Time=millis();
}

void loop() {
 acgy.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
  
   accPitch = (atan2(ax,az)) * RAD_TO_DEG;
   gyroYrate=gy/131.0;
   gyroYvalue=gyroYrate*(millis()-Time)/1000;
    Time=millis();
   combineread=0.98*(combineread+gyroYvalue)+(1-0.98)* accPitch ; // complementary filter
      Serial.print('\n');
      Serial.print(accPitch);
      output=Compute(combineread);
          
     SpeedControl(output);
}
double Compute(double input)
{  double error=setpoint-input;
   dt=millis()-previoustime;
   previoustime=millis();
  
    Iterm+=(error*ki*dt)/1000.0;
    if(Iterm>Max)
      Iterm=Max;
     else if(Iterm<Min)
       Iterm=Min;
    double change=input-lastinput;
     output=Iterm+kp*error+((change*kd*1000)/dt);
    if(output>Max)
     output=Max;
     else if(output<Min)
     output=Min;
     lastinput=input;
     return output;
    
}
 void SpeedControl(double output)
{
 if(output>0)
  {analogWrite(pin_a1,output);
  analogWrite(pin_a2,0);
  analogWrite(pin_b1,output);
  analogWrite(pin_b2,0);}
  else if(output<0){
    analogWrite(pin_a1,0);
  analogWrite(pin_a2,-output);
  analogWrite(pin_b1,0);
  analogWrite(pin_b2,-output);}
  else
   {analogWrite(pin_a1,0);
  analogWrite(pin_a2,0);
  analogWrite(pin_b1,0);
  analogWrite(pin_b2,0);}

}
