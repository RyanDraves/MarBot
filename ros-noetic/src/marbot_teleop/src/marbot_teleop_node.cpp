#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <wiringPi.h>
#include <ros/ros.h>

#include "marbot_teleop/robot.h"

using std::cerr;
using std::endl;

void test_robot_directional(Robot *robot)
{
    bool running;

    std_msgs::String msg;

    // msg.data = "w";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "W";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "d";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "D";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "s";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "S";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "a";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "A";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // msg.data = "q";
    // running = robot->updateControls(msg);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);

    ros::init(argc, argv, "marbot_teleop");

    wiringPiSetupGpio();

    Robot robot;

    ros::spin();

    return 0;
}
