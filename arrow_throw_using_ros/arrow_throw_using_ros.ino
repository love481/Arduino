#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#define enc_pin_channel1 2
#define proxy_pin 3
#define motor_pwm 5
#define motor_dir1 6
#define motor_dir2 7
#define pneu_for_wings 8
#define pneu_for_gear_stop 9
#define BV_(x,y) (x>>y)
uint8_t value=21;
ros::NodeHandle  nh;
std_msgs::UInt16 encCount;
std_msgs::UInt8 proxyStateCount;
std_msgs::UInt8 State;
//state defines 0,0,0,angle_state,motor_dir1,motor_dir2,pneu_for_wings,pneu_for_gear_stop
void messageCb(const std_msgs::UInt8& state) {
  // perform operation on motor and pneumatic
  State.data=state.data;
}
ros::Publisher encoder("pulse_count", &encCount);
ros::Subscriber<std_msgs::UInt8 > sub("pin_state", &messageCb);
void setup() {

  pinMode(enc_pin_channel1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enc_pin_channel1), ISR_for_encoder, RISING);
  pinMode(proxy_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(proxy_pin), ISR_for_proxy, RISING);

  pinMode(motor_pwm, OUTPUT);
  pinMode(motor_dir1, OUTPUT);
  pinMode(motor_dir2, OUTPUT);

  pinMode(pneu_for_wings, OUTPUT);
  pinMode(pneu_for_gear_stop, OUTPUT);
  Serial.begin(57600);
  nh.initNode();
  nh.advertise(encoder);
  nh.subscribe(sub);
  encCount.data = 0;
  proxyStateCount.data = 0;
}

void loop() {
   encoder.publish(&encCount);
   nh.spinOnce();
    delay(100);
  if (BV_(State.data, 4) & 1)
  {
    digitalWrite(motor_dir1, BV_(State.data, 3) & 1);
    digitalWrite(motor_dir2, BV_(State.data, 2) & 1);
    analogWrite(motor_pwm, 150);
    delay(100);
    digitalWrite(pneu_for_gear_stop, BV_(State.data, 0) & 1);
    Serial.println("yes");
  }
  else
  {
    digitalWrite(motor_dir1, BV_(State.data, 3) & 1);
    digitalWrite(motor_dir2, BV_(State.data, 2) & 1);
    analogWrite(motor_pwm, 0);
    digitalWrite(pneu_for_gear_stop, BV_(State.data, 0) & 1);
    delay(250);
    digitalWrite(pneu_for_wings, BV_(State.data, 1) & 1);
  }
}
void ISR_for_proxy()
{
  proxyStateCount.data++;
  if (proxyStateCount.data == 2)
  {
   // Serial.println("PneuForWingsActuated");
    digitalWrite(pneu_for_wings, HIGH);
    proxyStateCount.data = 0;

  }
}
void ISR_for_encoder()
{
  encCount.data++;
  if (proxyStateCount.data == 1)
  {
    encCount.data = 0;
   // Serial.println("EncoderValueStartedCounting");
  }

}
