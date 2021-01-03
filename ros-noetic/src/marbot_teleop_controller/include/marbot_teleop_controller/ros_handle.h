#ifndef ROS_HANDLE_H
#define ROS_HANDLE_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

#include <ros/ros.h>
#include <std_msgs/String.h>

class ROS_Handle {
public:
    ROS_Handle()
    {
        control_input_pub_ = nh_.advertise<std_msgs::String>("point_cloud_segments", 1);
    }
    void onKeyPress(const std::string &key)
    {
        std_msgs::String msg;
        msg.data = key;
        control_input_pub_.publish(msg);
    }
private:
    ros::NodeHandle nh_;
    ros::Publisher control_input_pub_;
};

#endif  /* ROS_HANDLE_H */
