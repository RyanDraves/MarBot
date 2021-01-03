#include <SDL2/SDL.h>
#include <iostream>

#include "marbot_teleop_controller/keyboard_controller.h"
#include "marbot_teleop_controller/ros_handle.h"

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);

    ROS_Handle handle;

    // https://codereview.stackexchange.com/questions/93488/c-keyboard-controller
    Controller keycontroller;

    // Bind keyboard methods
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_Q, std::bind(&ROS_Handle::onKeyPress, &handle, "q"));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_W, std::bind(&ROS_Handle::onKeyPress, &handle, "w"));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_W, std::bind(&ROS_Handle::onKeyPress, &handle, "W"));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_A, std::bind(&ROS_Handle::onKeyPress, &handle, "a"));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_A, std::bind(&ROS_Handle::onKeyPress, &handle, "A"));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_S, std::bind(&ROS_Handle::onKeyPress, &handle, "s"));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_S, std::bind(&ROS_Handle::onKeyPress, &handle, "S"));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_D, std::bind(&ROS_Handle::onKeyPress, &handle, "d"));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_D, std::bind(&ROS_Handle::onKeyPress, &handle, "D"));

    bool running = true;
    while (running)
    {
        /* Handle input and events: */
        SDL_Event sdl_event;
        SDL_WaitEvent(&sdl_event);
        switch (sdl_event.type)
        {
            case SDL_KEYDOWN:
            {
                // TODO: Find a better way to handle/bind Q. Could make every function return a boolean,
                // but only that one needs to
                if (sdl_event.key.keysym.scancode == SDL_SCANCODE_Q)
                {
                    running = false;
                    break;
                }
                keycontroller.OnKeyPress(sdl_event);
                break;
            }

            case SDL_KEYUP:
            {
                keycontroller.OnKeyRelease(sdl_event);
                break;
            }

            case SDL_QUIT:
            {
                running = false;
                break;
            }
        }
    }

    return 0;
}
