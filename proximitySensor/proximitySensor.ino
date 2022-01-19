int proximity_pin=5;
int proxState=0;
int releaPneu=6;
int count=1;
int flag=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(proximity_pin,INPUT);
  pinMode( releaPneu,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
    proxState=digitalRead(proximity_pin);
  if(proxState==0 && flag==0 )
   {
    if (count%2==0)
    {Serial.println("object Detected");
    //delay(100);
    digitalWrite(releaPneu,HIGH);
    delay(1000);
    }
    flag=1;
    count++;
    }
   else if(proxState==1)
   {
    Serial.println("object not Detected");
   digitalWrite(releaPneu,LOW);
   flag=0;
   }
}
