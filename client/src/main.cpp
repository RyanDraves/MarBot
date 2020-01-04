#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <chrono>
#include <string>

#include "robot.h"

using std::cerr;
using std::endl;

int main(int argc, char **argv)
{
    wiringPiSetupGpio();

    Robot robot;
    ZMQ_Handle client("192.168.1.143");

    bool running = true;
    while (running)
    {
        std::string state_cmds = client.getState();
        running = robot.updateControls(state_cmds);
        std::this_thread::sleep_for(std::chrono::milliseconds(10))
    }

    return 0;
}
