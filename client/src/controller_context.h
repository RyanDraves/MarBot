#ifndef CONTROLLER_CONTEXT_H
#define CONTROLLER_CONTEXT_H

// https://codereview.stackexchange.com/questions/93488/c-keyboard-controller

#include <vector>
#include <functional>

struct ControllerContext
{

    ControllerContext()
        : keyPressEvents(SDL_NUM_SCANCODES)
        , keyReleaseEvents(SDL_NUM_SCANCODES)
    {
        keyPressEvents.resize(SDL_NUM_SCANCODES);
        keyReleaseEvents.resize(SDL_NUM_SCANCODES);
    }

    typedef std::function<void(void)> KeyboardFunc_t;
    typedef std::vector<KeyboardFunc_t> KeyEvents;

    KeyEvents keyPressEvents;
    KeyEvents keyReleaseEvents;
};

typedef std::unique_ptr<ControllerContext> ControllerContext_ptr;

#endif