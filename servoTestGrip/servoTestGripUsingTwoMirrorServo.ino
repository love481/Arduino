
#include <Servo.h>

Servo servo1,servo2;

int pos = 0; 

void setup() {
 servo1.attach(11); 
 servo2.attach(12); 
 servo1.write(0);
 servo2.write(180);
 delay(3000); 
 for (pos = 0; pos <= 180; pos += 1) { 
    
 servo1.write(pos);
 servo2.write(180-pos);            
 delay(20);                 
}
 delay(3000);
 for (pos = 0; pos <= 180; pos += 1) { 
    
 servo1.write(180-pos);
 servo2.write(pos);            
 delay(20);                 
}
}

void loop() {

}

