#include "hiwr_simple_example.h"

HiwrSimpleExample::HiwrSimpleExample(ros::NodeHandle &n):
    nh_(n)
{
}

void HiwrSimpleExample::callbackTS(const hyve_msg::TouchEvent::ConstPtr & touch) {
    ROS_INFO("Entering callback TOUCH");

    pressed_ = touch->pressed;
}

void HiwrSimpleExample::callbackROI(const sensor_msgs::RegionOfInterest::ConstPtr &msg) {
    ROS_INFO("Catching someone's face");
    scenario_state_.data = "8";
    pub_scenario_.publish(scenario_state_);

    ros::Duration(1).sleep();
    scenario_state_.data = "6";
    pub_scenario_.publish(scenario_state_);
}

void HiwrSimpleExample::callbackTired(const std_msgs::UInt8::ConstPtr &msg){
 // ROS_INFO("Getting new tired value: %d and bright = %d", msg->data, last_brightness);	
//Retrieve first brightness value
  	last_brightness_ = msg->data;
  
	//Mean last_value with new data
	if((msg->data+last_brightness_)*0.5 < 25){
		is_sleeping_ = true;
    ROS_INFO("Going to sleep");
	}
	else is_sleeping_ = false;
}

void HiwrSimpleExample::loop(){
    ros::Rate loop_rate(10);
    pressed_ = false;
    ROS_INFO("Initializing subsriber");
    ros::Subscriber sub_ts;
    ros::Subscriber sub_roi;
    is_sleeping_ = false;
    last_brightness_ = -1;
    sub_ts = nh_.subscribe("/hiwr_touchscreen/touch_event",1, &HiwrSimpleExample::callbackTS,this);
    //sub_roi = nh.subscribe<sensor_msgs::RegionOfInterest>("/hiwr_opencv_detector/roi", 1, &HiwrSimpleExample::callbackROI, this);
    pub_scenario_ = nh_.advertise<std_msgs::String>("/scenario/state", 1);
    sub_tired_ = nh_.subscribe("/hiwr_tired/brightness", 1, &HiwrSimpleExample::callbackTired, this);
    bool send_sleep = false;
    bool send_wakeup = false;
    while(ros::ok()) {
        if(pressed_ && !is_sleeping_) {

            ROS_INFO("Pressed");
            scenario_state_.data = "7"; // grumpy face
            pub_scenario_.publish(scenario_state_);
            ros::Duration(2).sleep();
            scenario_state_.data = "6";
            pub_scenario_.publish(scenario_state_);
            //ros::Publisher pub = nh.advertise<hyve_msg::TouchEvent>("hyve_screen", sizeof(hyve_msg::TouchEvent));

        }else if(is_sleeping_ && !send_sleep){
		scenario_state_.data="3";
		pub_scenario_.publish(scenario_state_);
		ros::Duration(1).sleep();
        scenario_state_.data="4";
		pub_scenario_.publish(scenario_state_);
		send_sleep = true;
		send_wakeup = false;	
	}else if(!is_sleeping_ && !send_wakeup){
        scenario_state_.data="6";
        pub_scenario_.publish(scenario_state_);
		
		send_sleep = false;
		send_wakeup = true;
	}
        loop_rate.sleep();
        ros::spinOnce();
    }
}


int main(int argc, char ** argv) {
    ROS_INFO("Initializing...");
    ros::init(argc, argv, "HiwrSimpleExample");
    ros::NodeHandle n;

    HiwrSimpleExample node(n);
    node.loop();


}


