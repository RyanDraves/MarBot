#include <SDL2/SDL.h>
#include <iostream>
#include <wiringPi.h>

#include "keyboard_controller.h"
#include "robot.h"

using std::cerr;
using std::endl;

int main(int argc, char **argv)
{
    wiringPiSetupGpio();

    // https://codereview.stackexchange.com/questions/93488/c-keyboard-controller
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        /* Handle problem */
        fprintf(stderr, "%s\n", SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow("Window caption", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 852, 480, 0);
    if (window == NULL)
    {
        /* Handle problem */
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        /* Handle problem */
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_Quit();
    }

    cerr << "-------------------------------------" << endl;
    cerr << "Use WASD to control. Press q to quit." << endl;
    cerr << "-------------------------------------" << endl;

    Controller keycontroller;

    // Bind keyboard methods
    Robot robot;
    keycontroller.SetPressCallback(SDL_SCANCODE_W, std::bind(&Robot::onForwardPress, robot));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_W, std::bind(&Robot::onForwardRelease, robot));
    keycontroller.SetPressCallback(SDL_SCANCODE_D, std::bind(&Robot::onRightPress, robot));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_D, std::bind(&Robot::onRightRelease, robot));
    keycontroller.SetPressCallback(SDL_SCANCODE_S, std::bind(&Robot::onBackwardPress, robot));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_S, std::bind(&Robot::onBackwardRelease, robot));
    keycontroller.SetPressCallback(SDL_SCANCODE_A, std::bind(&Robot::onLeftPress, robot));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_A, std::bind(&Robot::onLeftRelease, robot));

    bool running = true;
    while (running)
    {
        /* Clear the buffer of color, setting it to black */
        SDL_RenderClear(renderer);

        /* Draw the buffer into the window */
        SDL_RenderPresent(renderer);

        /* Handle input and events: */
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event) > 0)
        {
            switch (sdl_event.type)
            {
                case(SDL_KEYDOWN):
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

                case(SDL_KEYUP):
                {
                    keycontroller.OnKeyRelease(sdl_event);
                    break;
                }

                case(SDL_QUIT):
                {
                    running = false;
                    break;
                }
            }
        }

        robot.updateControls();
    }

    SDL_Quit();

    return 0;
}