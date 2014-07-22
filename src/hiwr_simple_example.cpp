/*********************************************************************
*
*
* Copyright 2014 Worldline
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***********************************************************************/

#include "hiwr_simple_example.h"

HiwrSimpleExample::HiwrSimpleExample(ros::NodeHandle &n):
    nh_(n)
{
}

void HiwrSimpleExample::callbackTS(const hiwr_msg::TouchEvent::ConstPtr & touch) {
    ROS_DEBUG("Entering callback TOUCH");

    pressed_ = touch->pressed;
}

void HiwrSimpleExample::callbackTired(const std_msgs::UInt8::ConstPtr &msg){
    //Retrieve first brightness value
  	last_brightness_ = msg->data;
  
	//Mean last_value with new data
	if((msg->data+last_brightness_)*0.5 < 25){
		is_sleeping_ = true;
        ROS_DEBUG("Going to sleep");
	}
	else is_sleeping_ = false;
}

void HiwrSimpleExample::loop(){
    ros::Rate loop_rate(10);

    pressed_ = false;
    is_sleeping_ = false;
    send_sleep_ = false;
    send_wakeup_ = false;
    last_brightness_ = -1;

    ROS_DEBUG("Initializing subsriber");
    sub_ts_ = nh_.subscribe("/hiwr_touchscreen/touch_event",1, &HiwrSimpleExample::callbackTS,this);
    sub_tired_ = nh_.subscribe("/hiwr_tired/brightness", 1, &HiwrSimpleExample::callbackTired, this);

    pub_scenario_ = nh_.advertise<std_msgs::String>("/scenario/state", 1);

    while(ros::ok()) {
        // Touchscreen pressed
        if(pressed_ && !is_sleeping_) {
            ROS_DEBUG("Pressed");

            //Display grumpy face
            scenario_state_.data = "7";
            pub_scenario_.publish(scenario_state_);

            ros::Duration(2).sleep();

            //Back to normal head
            scenario_state_.data = "6";
            pub_scenario_.publish(scenario_state_);

        }else if(is_sleeping_ && !send_sleep_){
            // Hiwr being tired
            scenario_state_.data="3";
            pub_scenario_.publish(scenario_state_);

            ros::Duration(1).sleep();

            // Hiwr sleepy
            scenario_state_.data="4";
            pub_scenario_.publish(scenario_state_);

            send_sleep_ = true;
            send_wakeup_ = false;
        }else if(!is_sleeping_ && !send_wakeup_){
            // Awake
            scenario_state_.data="6";
            pub_scenario_.publish(scenario_state_);

            send_sleep_ = false;
            send_wakeup_ = true;
        }

        loop_rate.sleep();
        ros::spinOnce();
    }
}

int main(int argc, char ** argv) {
    ROS_DEBUG("Initializing...");
    ros::init(argc, argv, "HiwrSimpleExample");
    ros::NodeHandle n;

    HiwrSimpleExample node(n);
    node.loop();
}


