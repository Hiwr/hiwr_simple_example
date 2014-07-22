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

//Common
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
//#include <dlfcn.h>
#include <unistd.h>

// ROS
#include "ros/ros.h"
#include <ros/time.h>
#include "rospack/rospack.h"

// Messages
#include "sensor_msgs/RegionOfInterest.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8.h"

// Service Msgs
#include <hiwr_msg/SetState.h>
#include <hiwr_msg/GetState.h>

// TouchScreen Msgs
#include "hiwr_msg/TouchEvent.h"


#include <pluginlib/class_list_macros.h>

class HiwrSimpleExample {
public:
    HiwrSimpleExample(ros::NodeHandle &);
    void loop();

protected:

private:
    ros::NodeHandle nh_;

    std_msgs::String scenario_state_;

    // Publishers
    ros::Publisher pub_scenario_;

    //Subscribers
    ros::Subscriber sub_tired_;
    ros::Subscriber sub_ts_;

    // Hiwr states
    bool is_sleeping_;
    bool pressed_;
    bool send_sleep_;
    bool send_wakeup_;

    int last_brightness_;

    void callbackTS(const hiwr_msg::TouchEvent::ConstPtr & touch);
    void callbackTired(const std_msgs::UInt8::ConstPtr &);

};
