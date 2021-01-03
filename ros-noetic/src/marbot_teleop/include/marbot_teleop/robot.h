#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#include <ros/ros.h>
#include <std_msgs/String.h>

#include "motor.h"

enum DIRECTION { FORWARD, LEFT, BACKWARD, RIGHT };

class Robot
{
public:
    Robot();
    Robot(int l_1, int l_2, int r_1, int r_2);
    void updateControls(const std_msgs::String &state_cmds);
private:
    bool processCmds(const std::string &std_cmds);

    Motor l_motor_;
    Motor r_motor_;

    std::vector<bool> direction_;

    ros::NodeHandle nh_;

    ros::Subscriber control_input_sub_;
};

#endif  // ROBOT_H
