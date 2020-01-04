#include <SDL2/SDL.h>
#include <iostream>

#include "keyboard_controller.h"
#include "gui.h"
#include "zmq_handle.h"

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);

    Gui gui;
    ZMQ_Handle server;

    // https://codereview.stackexchange.com/questions/93488/c-keyboard-controller
    Controller keycontroller;

    // Bind keyboard methods
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_W, std::bind(&Gui::onWPress, &gui));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_W, std::bind(&Gui::onWRelease, &gui));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_A, std::bind(&Gui::onAPress, &gui));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_A, std::bind(&Gui::onARelease, &gui));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_S, std::bind(&Gui::onSPress, &gui));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_S, std::bind(&Gui::onSRelease, &gui));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_D, std::bind(&Gui::onDPress, &gui));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_D, std::bind(&Gui::onDRelease, &gui));

    keycontroller.SetPressOnceCallback(SDL_SCANCODE_Q, std::bind(&ZMQ_Handle::onQPress, &server));

    keycontroller.SetPressOnceCallback(SDL_SCANCODE_W, std::bind(&ZMQ_Handle::onWPress, &server));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_W, std::bind(&ZMQ_Handle::onWRelease, &server));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_A, std::bind(&ZMQ_Handle::onAPress, &server));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_A, std::bind(&ZMQ_Handle::onARelease, &server));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_S, std::bind(&ZMQ_Handle::onSPress, &server));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_S, std::bind(&ZMQ_Handle::onSRelease, &server));
    keycontroller.SetPressOnceCallback(SDL_SCANCODE_D, std::bind(&ZMQ_Handle::onDPress, &server));
    keycontroller.SetReleaseCallback(SDL_SCANCODE_D, std::bind(&ZMQ_Handle::onDRelease, &server));

    bool running = true;
    while (running)
    {
        gui.renderScreen();

        /* Handle input and events: */
        SDL_Event sdl_event;
        SDL_WaitEvent(&sdl_event);
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

    // Resource freeing handled by gui destructor

    return 0;
}
