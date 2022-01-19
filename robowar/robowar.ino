#define L1 12
#define L2 10
#define R2 8
#define R1 9


char d = 'S';

void setup() {
  // put your setup code here, to run once:
  pinMode(L1,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R2,OUTPUT);
//  pinMode(P1,OUTPUT);
 // pinMode(P2,OUTPUT);

  Serial.begin(9600);
  Serial2.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
//  analogWrite(P1,100);
  //analogWrite(P2,200);

  if(Serial2.available()){
    d = Serial2.read();
    Serial.println(d);
  }

  switch(d){
    case 'F':
      digitalWrite(L1,HIGH);
      digitalWrite(R1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(R2,LOW);
      break;

   case 'B':
      digitalWrite(L2,HIGH);
      digitalWrite(R2,HIGH);
      digitalWrite(L1,LOW);
      digitalWrite(R1,LOW);
      break;

   case 'G':
      digitalWrite(L1,LOW);
      digitalWrite(R1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(R2,LOW);
      break;

 case 'R':
      digitalWrite(L1,HIGH);
      digitalWrite(R1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(R2,LOW);
      break;
  case 'L':
      digitalWrite(L1,LOW);
      digitalWrite(R1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(R2,LOW);
      break;

  case 'I':
      digitalWrite(L1,HIGH);
      digitalWrite(R1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(R2,HIGH);
      break;
 case 'H':
      digitalWrite(L1,HIGH);
      digitalWrite(R1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(R2,HIGH);
      break;
 case 'J':
    digitalWrite(L1,LOW);
      digitalWrite(R1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(R2,LOW);
      break;
  case 'S':
      digitalWrite(L1,LOW);
      digitalWrite(R1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(R2,LOW);
      break;

  default:
      break;
  }
}
