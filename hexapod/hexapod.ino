#include <Servo.h>  
Servo s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13;

int a=0, default_angle = 90, da = default_angle;
bool straight = true, back = true, rotateR = true, rotateL = true, st1 = true, st2 = true, st3 = true, st4 = true, st5 = true, st6 = true;


void d(int i=0)
{
  delay(20+i);
}

void check_keys()
{
  
}

void initialize(int i = 0)
{
  int ld = 50;
  if (i == 0)         // resets all
  {
  s2.attach(2);
  s3.attach(3);
  s4.attach(4);         // negative for anti-clowkwise
  s5.attach(5);
  s6.attach(6);
  s7.attach(7);         // negative for upward
  s8.attach(8);
  s9.attach(9);
  s10.attach(10);
  s11.attach(11);
  s12.attach(12);
  s13.attach(13);


  s2.write(default_angle);
  d(ld);
  s3.write(default_angle);
  d(ld);
  s4.write(default_angle);
  d(ld);
  s5.write(default_angle);
  d(ld);
  s6.write(default_angle);
  d(ld);
  s7.write(default_angle);
  d(ld);
  s8.write(default_angle);
  d(ld);
  s9.write(default_angle);
  d(ld);
  s10.write(default_angle);
  d(ld);
  s11.write(default_angle);
  d(ld);
  s12.write(default_angle);
  d(ld);
  s13.write(default_angle);
  d(ld); 
  }
  if (i == 1)     //reset upper arm
  {
  s2.write(default_angle);
  d(ld);
  s4.write(default_angle);
  d(ld);
  s6.write(default_angle);
  d(ld);
  s8.write(default_angle);
  d(ld);
  s10.write(default_angle);
  d(ld);
  s12.write(default_angle);
  d(ld);
 
  }

  if (i == 2) // resets lower arm
  {
  s13.write(default_angle);
  d(ld);
  s11.write(default_angle);
  d(ld);
  s9.write(default_angle);
  d(ld);
  s7.write(default_angle);
  d(ld);
  s5.write(default_angle);
  d(ld);
  s3.write(default_angle);
  d(ld); 
  }
  
}

void set_normal(int SN,int ld = 0)
{
  Servo ss;
  ss.attach(SN);
  ss.write(default_angle);
  d(ld);
}


void style(int i, int ld = 1000)
{
  if (i == 1)
  {
  s3.write(da+60);
  d(ld);
  set_normal(3);
  s5.write(da+60);
  d(ld);
  set_normal(5);
  s7.write(da+60);
  d(ld);
  set_normal(7);
  s9.write(da+60);
  d(ld);
  set_normal(9);
  s11.write(da+60);
  d(ld);
  set_normal(11);
  s13.write(da+60);
  d(ld);
  set_normal(13);
  }
  if (i == 2)
  {
    s5.write(da+60);
    d(ld);
    s9.write(da+60);
    d(ld);
    s13.write(da+60);
    d(ld);
  }
 
}


void walk(int i = 0)                                        // 0 for normal walk (F, B, L, R), 1 for rotate in clockwise and -1 for anti-clockwise, 
{
  int a1 = 45, a2 = 45, ld =20, temp = 0, front = 20;       // a1 for main leg and a2 for secondary leg
  if (i == 0)     //normal walk
  {
    check_keys();
    if(straight || st1)                               //First step
    {
    s3.write(90+a1);d(ld);
    s7.write(90+a2);d(ld);
    s11.write(90+a2);d(ld);              //missing
    s6.write(90+a1);d(ld);
    s10.write(90+a1);d(ld);
    d(ld*3); 
    check_keys();
    }
    
    if (straight || st2)                              //Second step
    {
    s7.write(90);d(ld);
    s11.write(90);d(ld);                               //missing  
    check_keys();
    }
    
    if(straight || st3)                                //Third step
    {
    s3.write(90-front);d(ld);
    s6.write(90+temp);d(ld);
    s10.write(90+temp);d(ld);
    d(ld*3);
    check_keys();
    }

    if(straight  ||  st4)                             //Fourth step
    {
    s13.write(90+a1);d(ld);
    s5.write(90+a2);d(ld);
    s9.write(90+a2);d(ld);           
    s4.write(90+a1);d(ld);
    s8.write(90-a1);d(ld);
    d(ld*3);  
    check_keys();
    }
    
    if(straight  || st5)                        //Fifth step
    {
    s5.write(90);d(ld);
    s9.write(90);d(ld);  
    check_keys();
    }
            
    if(straight  || st6 )                        //Sixth step
    {
     s13.write(90-front);d(ld);
    s4.write(90+temp);d(ld);
    s8.write(90-temp);d(ld);
    d(ld*3);
    check_keys();
    }
    
  }
}


void fold(int i = 1)      // 1 for folding and 0 for unfolding
{
  int  ld = 100, fa_even = 20, fa_odd = 150;
  if (i == 1)
  {
    s2.write(fa_even);d(ld);
    s4.write(180);d(ld);
    s6.write(fa_even);d(ld);
    s8.write(fa_even);d(ld);
    s10.write(fa_even);d(ld);
    s12.write(fa_even);d(ld);
    
    s3.write(fa_odd);d(ld);
    s5.write(fa_odd);d(ld);
    s7.write(180 - fa_odd);d(ld);
    s9.write(fa_odd);d(ld);
    s11.write(fa_odd);d(ld);          //missing
    s13.write(fa_odd);d(ld);
  }
  if (i == 0)
  {
    ld = 100; fa_even = da; fa_odd = da;
    s2.write(fa_even);d(ld);
    s4.write(fa_even);d(ld);
    s6.write(fa_even);d(ld);
    s8.write(fa_even);d(ld);
    s10.write(fa_even);d(ld);
    s12.write(fa_even);d(ld);
    
    s3.write(fa_odd);d(ld);
    s5.write(fa_odd);d(ld);
    s7.write(fa_odd);d(ld);
    s9.write(fa_odd);d(ld);
    s11.write(fa_odd);d(ld);          //missing
    s13.write(fa_odd);d(ld);
  }
}
void setup() 
{
   initialize();
   delay(3000);
}


void loop() 
{
  
  walk();
}
