// ROS Default Header File
#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>
#define motor_to_gearReduction 2.05
#define ppr (250*motor_to_gearReduction)
#define BV_(x) (1<<x)
//state defines 0,0,0,angle_state,motor_dir1,motor_dir2,pneu_for_wings,pneu_for_gear_stop
std_msgs::Float32 AngleEncoder;
std_msgs::UInt8 state;
std_msgs::UInt16 encCount;
void processEncoderData()
{
  if(AngleEncoder.data<=11.5)
  {
  AngleEncoder.data=(2*3.14*encCount.data)/ppr;
  state.data=BV_(0)|BV_(2)|BV_(4);
  }
  else
  {
    state.data=BV_(1);
  }
}
void msgCallback(std_msgs::UInt16 count)
{
  ROS_INFO("receive encoder count = %u",count.data);
  encCount.data=count.data;
}
int main(int argc, char **argv)			
{
AngleEncoder.data=0;
state.data=0;
ros::init(argc, argv, "throwing_node");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe("pulse_count", 1000, msgCallback);
ros::Publisher  pub = nh.advertise<std_msgs::UInt8>("pin_state", 1000);
ros::Rate loop_rate(10);
while(ros::ok())
{
pub.publish(state);
processEncoderData();
ROS_INFO("transmitt pin state = %d",state.data);
ros::spinOnce();
loop_rate.sleep();
}
}
