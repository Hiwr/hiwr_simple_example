#include "hiwr_simple_example.h"

Hiwr_simple_example::Hiwr_simple_example(ros::NodeHandle &n):
    nh(n)
{
}

void Hiwr_simple_example::callbackTS(const hyve_msg::TouchEvent::ConstPtr & touch) {
    ROS_INFO("Entering callback TOUCH");

    pressed = touch->pressed;
}

void Hiwr_simple_example::callbackROI(const sensor_msgs::RegionOfInterest::ConstPtr &msg) {
    ROS_INFO("Catching someone's face");
    scenarioState.data = "8";
    pub_Scenario.publish(scenarioState);

    ros::Duration(1).sleep();
    scenarioState.data = "6";
    pub_Scenario.publish(scenarioState);
}

void Hiwr_simple_example::callbackTired(const std_msgs::UInt8::ConstPtr &msg){
 // ROS_INFO("Getting new tired value: %d and bright = %d", msg->data, last_brightness);	
//Retrieve first brightness value
  	last_brightness = msg->data;
  
	//Mean last_value with new data
	if((msg->data+last_brightness)*0.5 < 25){
		isSleeping = true;
    ROS_INFO("Going to sleep");
	}
	else isSleeping = false;
}

void Hiwr_simple_example::loop(){
    ros::Rate loop_rate(10);
    pressed = false;
    ROS_INFO("Initializing subsriber");
    ros::Subscriber sub_ts;
    ros::Subscriber sub_roi;
    isSleeping = false;
    last_brightness = -1;
    sub_ts = nh.subscribe("/hiwr_touchscreen/touch_event",1, &Hiwr_simple_example::callbackTS,this);
    //sub_roi = nh.subscribe<sensor_msgs::RegionOfInterest>("/hiwr_opencv_detector/roi", 1, &Hiwr_simple_example::callbackROI, this);
    pub_Scenario = nh.advertise<std_msgs::String>("/scenario/state", 1);
    sub_tired = nh.subscribe("/hiwr_tired/brightness", 1, &Hiwr_simple_example::callbackTired, this);
    bool sendSleep = false;
    bool sendWakeup = false;
    while(ros::ok()) {
        if(pressed && !isSleeping) {

            ROS_INFO("Pressed");
            scenarioState.data = "7"; // grumpy face
            pub_Scenario.publish(scenarioState);
            ros::Duration(2).sleep();
            scenarioState.data = "6";
            pub_Scenario.publish(scenarioState);
            //ros::Publisher pub = nh.advertise<hyve_msg::TouchEvent>("hyve_screen", sizeof(hyve_msg::TouchEvent));

        }else if(isSleeping && !sendSleep){
		scenarioState.data="3";
		pub_Scenario.publish(scenarioState);
		ros::Duration(1).sleep();
		scenarioState.data="4";
		pub_Scenario.publish(scenarioState);
		sendSleep = true;
		sendWakeup = false;	
	}else if(!isSleeping && !sendWakeup){
		scenarioState.data="6";
		pub_Scenario.publish(scenarioState);
		
		sendSleep = false;
		sendWakeup = true;
	}
        loop_rate.sleep();
        ros::spinOnce();
    }
}


int main(int argc, char ** argv) {
    ROS_INFO("Initializing...");
    ros::init(argc, argv, "hiwr_simple_example");
    ros::NodeHandle n;

    Hiwr_simple_example node(n);
    node.loop();


}


