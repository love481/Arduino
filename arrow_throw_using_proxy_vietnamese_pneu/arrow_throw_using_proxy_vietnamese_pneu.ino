#define motor_to_gearReduction 2.05
#define ppr (250*2.05)
#define enc_pin_channel1 2
#define proxy_pin 3
#define motor_pwm 6
#define motor_dir1 7
#define motor_dir2 8
#define pneu_for_wings 5
#define pneu_for_gear_stop 4
int proxyStateCount=0;
bool state=false;
int encCount=0;
float AngleEncoder=0;
uint16_t t=0;
void setup() {
 pinMode(enc_pin_channel1,INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(enc_pin_channel1),ISR_for_encoder,RISING);
 pinMode(proxy_pin,INPUT);
 attachInterrupt(digitalPinToInterrupt(proxy_pin),ISR_for_proxy,RISING);
 pinMode(motor_pwm,OUTPUT);
 pinMode(motor_dir1,OUTPUT);
 pinMode(motor_dir2,OUTPUT);
 //pinMode(pneu_for_wings,OUTPUT);
 pinMode(pneu_for_gear_stop,OUTPUT);
 Serial.begin(9600); 
}
void setEncPneu()
{

 if(proxyStateCount==1 && state==false)
  {
    encCount=0;
    Serial.println("EncoderValueStartedCounting");
    state=true;
  }

   if(proxyStateCount==2 && state==true)
   {
    Serial.println("PneuForWingsActuated");
     //digitalWrite(pneu_for_wings,HIGH);
    proxyStateCount=0;
    state=false;
    
   }
}
void loop() {
 t=millis();
 while(AngleEncoder<=7)
  {
   setEncPneu();
  AngleEncoder=(2*3.14*encCount)/ppr;
  digitalWrite(motor_dir1,LOW);
   digitalWrite(motor_dir2,HIGH);
   analogWrite(motor_pwm,255);
    if((millis()-t)>100)
   {
    digitalWrite(pneu_for_gear_stop,HIGH);
    t=millis();
   }
   //delay(100);
   //digitalWrite(pneu_for_gear_stop,HIGH);
  }
  digitalWrite(motor_dir1,LOW);
  digitalWrite(motor_dir2,LOW);
  analogWrite(motor_pwm,0);
  digitalWrite(pneu_for_gear_stop,LOW);
  //delay(250);
  //digitalWrite(pneu_for_wings,HIGH);
 
}
void ISR_for_proxy()
{
 proxyStateCount++;
}
void ISR_for_encoder()
{
  encCount++;
  
}
