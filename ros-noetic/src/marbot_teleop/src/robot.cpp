#include "marbot_teleop/robot.h"

Robot::Robot()
  : l_motor_(9, 10),
    r_motor_(8, 7),
    direction_(4, false) 
{
    control_input_sub_ = nh_.subscribe("/control/input", 10, &Robot::updateControls, this);
}

Robot::Robot(int l_1, int l_2, int r_1, int r_2)
  : l_motor_(l_1, l_2),
    r_motor_(r_1, r_2)
{
    control_input_sub_ = nh_.subscribe("/control/input", 10, &Robot::updateControls, this);
}

void Robot::updateControls(const std_msgs::String &state_cmds)
{
    bool running = processCmds(state_cmds.data);

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
    r_motor_.set(-(forward_val - side_val));
}

bool Robot::processCmds(const std::string &std_cmds)
{
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
            default:
                break;
        }
        if (q_flag) break;
    }
    if (q_flag) return false;
    return true;
}
