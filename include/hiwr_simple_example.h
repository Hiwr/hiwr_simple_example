#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Touchscreen export
#include "ros/ros.h"
#include "rospack/rospack.h"
#include "hyve_msg/TouchEvent.h"

// Facetracking export
#include <dlfcn.h>
#include <unistd.h>
#include <signal.h>
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <ros/time.h>
#include "std_msgs/String.h"
#include "std_msgs/UInt8.h"
#include <hyve_msg/SetState.h>
#include <hyve_msg/GetState.h>
#include <std_msgs/String.h>
#include "sensor_msgs/RegionOfInterest.h"
#include <string.h>


#include <pluginlib/class_list_macros.h>

class HiwrSimpleExample {
public:
    void callbackTS(const hyve_msg::TouchEvent::ConstPtr & touch);
    void callbackROI(const sensor_msgs::RegionOfInterest::ConstPtr &msg);
    void callbackTired(const std_msgs::UInt8::ConstPtr &);
    void loop();

    HiwrSimpleExample(ros::NodeHandle &);
    ros::NodeHandle nh_;
    bool pressed_;
    std_msgs::String scenario_state_;
    ros::Publisher pub_scenario_;
    ros::Subscriber sub_tired_;
    bool is_sleeping_;
    int last_brightness_;
protected:

private:

};
