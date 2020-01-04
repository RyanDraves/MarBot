#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <chrono>
#include <string>

#include "robot.h"
#include "zmq_handle.h"

using std::cerr;
using std::endl;

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);

    wiringPiSetupGpio();

    Robot robot;
    ZMQ_Handle client("192.168.1.143");

    bool running = true;
    while (running)
    {
        std::string state_cmds = client.getState();
        running = robot.updateControls(state_cmds);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
