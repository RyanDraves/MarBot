#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#include "motor.h"

enum DIRECTION { FORWARD, LEFT, BACKWARD, RIGHT };

class Robot
{
public:
    Robot() :
        l_motor_(8, 7),
        r_motor_(9, 10),
        direction_(4, false) {}
    Robot(int l_1, int l_2, int r_1, int r_2) :
        l_motor_(l_1, l_2),
        r_motor_(r_1, r_2) {}
    bool updateControls(const std::string &state_cmds)
    {
        bool running = processCmds(state_cmds);

        int forward = 0;
        int side = 0;

        if (direction_[FORWARD]) forward += 1;
        if (direction_[BACKWARD]) forward -= 1;
        if (direction_[RIGHT]) side += 1;
        if (direction_[LEFT]) side -= 1;

        // Normalize the output
        int sum = std::abs(forward) + std::abs(side);

        double forward_val = sum > 0 ? static_cast<double>(forward) / sum : 0;
        double side_val = sum > 0 ? static_cast<double>(side) / sum : 0;

        // std::cerr << "left: " << forward_val + side_val << " right: " << forward_val - side_val << std::endl;
        l_motor_.set(forward_val + side_val);
        r_motor_.set(forward_val - side_val);

        return running;
    }
private:
    bool processCmds(const std::string &std_cmds) {
        bool q_flag = false;
        for (const auto &cmd : std_cmds) {
            switch (cmd) {
                case 'q':
                {
                    direction_[FORWARD] = false;
                    direction_[LEFT] = false;
                    direction_[BACKWARD] = false;
                    direction_[RIGHT] = false;
                    q_flag = true;
                    break;
                }
                case 'w':
                    direction_[FORWARD] = true;
                    break;
                case 'W':
                    direction_[FORWARD] = false;
                    break;
                case 'a':
                    direction_[LEFT] = true;
                    break;
                case 'A':
                    direction_[LEFT] = false;
                    break;
                case 's':
                    direction_[BACKWARD] = true;
                    break;
                case 'S':
                    direction_[BACKWARD] = false;
                    break;
                case 'd':
                    direction_[RIGHT] = true;
                    break;
                case 'D':
                    direction_[RIGHT] = false;
                    break;
            }
            if (q_flag) break;
        }
        if (q_flag) return false;
        return true;
    }

    Motor l_motor_;
    Motor r_motor_;

    std::vector<bool> direction_;
};

#endif  // ROBOT_H
