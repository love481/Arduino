#define ppr 475
#define enc_pin 2
#define motor_pwm 3
#define dir_pin1 7
#define dir_pin2 5
uint16_t Count=0;
double rpm=0,sample_time=10,arm_angle=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enc_pin,INPUT_PULLUP);
  pinMode(dir_pin1,OUTPUT);
  pinMode(dir_pin2,OUTPUT);
  pinMode(motor_pwm,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enc_pin),update_count,RISING);
  while(arm_angle<((40*3.14)/180))
  {digitalWrite(dir_pin1,LOW);
  digitalWrite(dir_pin2,HIGH);
  analogWrite(motor_pwm,255);
  arm_angle=((2*3.14*(double)Count)/ppr);
  Serial.println("angle is:"+String(arm_angle));
  Serial.println("Count is:"+String(Count));
  Serial.println();
  }
  Count=0;
  arm_angle=0;
    while(arm_angle<((60*3.14)/180))
  {digitalWrite(dir_pin1,HIGH);
  digitalWrite(dir_pin2,LOW);
  analogWrite(motor_pwm,250);
  arm_angle=((2*3.14*(double)Count)/ppr);
  Serial.println("angle is:"+String(arm_angle));
  Serial.println("Count is:"+String(Count));
  Serial.println();
  }
  digitalWrite(dir_pin1,LOW);
  digitalWrite(dir_pin2,LOW);
  analogWrite(motor_pwm,0);
  
}

void loop() {
 
}
void update_count()
{
  Count++;
}
