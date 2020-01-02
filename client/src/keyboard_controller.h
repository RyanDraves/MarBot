#ifndef KEYBOARDCONTROLLER_H_
#define KEYBOARDCONTROLLER_H_

// https://codereview.stackexchange.com/questions/93488/c-keyboard-controller

#include <map>
#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <string>
#include <memory>

#include "controller_context.h"

class Controller
{
public:
    Controller();

    bool OnKeyPress(const SDL_Event &e);

    bool OnKeyRelease(const SDL_Event &e);

    // TODO: Add functionality for SetPressOnce by keeping track of held keys

    // Clear by setting empty func
    void SetReleaseCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t & func);
    void SetPressCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t & func);

    // Clear both press and release
    void ClearCallback(SDL_Scancode code);

protected:
    ControllerContext_ptr controller_context_;
};

#endif