#define ppr (328*2.45)
#define enc_pin 2
uint16_t Count=0;
double rpm=0,motorpwm=0,sample_time=500;
long prev_time=0,curr_time=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enc_pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enc_pin),update_count,RISING);
  prev_time=millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  curr_time=millis();
  if(curr_time>sample_time+prev_time){
    prev_time=curr_time;
    rpm=((Count*60000)/(ppr*sample_time));
    Serial.println("rpm is:"+String(rpm));
    Serial.println("pulse is:"+String(Count));
    Serial.println();
   Count=0;
  }
  Serial.println("pulse is:"+String(Count));

}
void update_count()
{
  Count++;
}
