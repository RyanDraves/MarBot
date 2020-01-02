#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <cmath>

#include "motor.h"

enum DIRECTION = { FOWARD, LEFT, BACKWARD, RIGHT };

class Robot
{
public:
    Robot() : 
        l_motor_(8, 7),
        r_motor_(9, 10)
    {
        direction_.resize(4);
        for (bool &e : direction_) {
            e = false;
        }
    }
    Robot(int l_1, int l_2, int r_1, int r_2)
    {
        l_motor_(l_1, l_2);
        r_motor_(r_1, r_2);
    }
    void update_controls()
    {
        int forward = 0;
        int side = 0;

        if (direction_[FORWARD]) forward += 1;
        if (direction_[BACKWARD]) forward -= 1;
        if (direction_[RIGHT]) side += 1;
        if (direction_[LEFT]) side -= 1;

        // Normalize the output
        int sum = std::abs(foward) + std::abs(side);

        double forward_val = static_cast<double>(forward / sum);
        double side_val = static_cast<double>(side / sum);

        l_motor_.set(forward_val + side_val);
        r_motor_.set(forward_val + side_val);
    }
    void onForwardPress()
    {
        direction_[FOWARD] = true;
    }
    void onForwardRelease()
    {
        direction_[FORWARD] = false;
    }
    void onRightPress()
    {
        direction_[RIGHT] = true;
    }
    void onRightRelease()
    {
        direction_[RIGHT] = false;
    }
    void onBackwardPress()
    {
        direction_[BACKWARD] = true;
    }
    void onBackwardRelease()
    {
        direction_[BACKWARD] = false;
    }
    void onLeftPress()
    {
        direction_[LEFT] = true;
    }
    void onLeftRelease()
    {
        direction_[LEFT] = false;
    }
private:
    Motor l_motor_;
    Motor r_motor_;

    std::vector<bool> direction_;
};

#endif  // ROBOT_H
