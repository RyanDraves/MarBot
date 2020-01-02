#include "keyboard_controller.h"
#include "controller_context.h"

// https://codereview.stackexchange.com/questions/93488/c-keyboard-controller

Controller::Controller()
    : controller_context_(new ControllerContext())
{
    //Some test initializations
    auto leftPress = [&]()
    {
        // Left press lambda
        int debug=0;
    };
    auto leftRelease = [&]()
    {
        // Left release lambda
        int debug=0;
    };

    SetPressCallback(SDL_SCANCODE_LEFT, leftPress);
    SetReleaseCallback(SDL_SCANCODE_LEFT, leftRelease);
}

bool Controller::OnKeyPress(const SDL_Event &e)
{
    const auto & scancode = e.key.keysym.scancode;

    const auto & pressFunc = controller_context_->keyPressEvents[scancode];

    if (pressFunc)
    {
        // Call callback if valid
        pressFunc();
        return true;
    }

    return false;
}

bool Controller::OnKeyRelease(const SDL_Event &e)
{
    const auto & scancode = e.key.keysym.scancode;

    const auto & pressFunc = controller_context_->keyReleaseEvents[scancode];

    if (pressFunc)
    {
        // Call callback if valid
        pressFunc();

        return true;
    }

    return false;
}

void Controller::SetReleaseCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t &func)
{
    controller_context_->keyReleaseEvents[code] = func; 
}

void Controller::SetPressCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t &func)
{
    controller_context_->keyPressEvents[code] = func;
}

void Controller::ClearCallback(SDL_Scancode code)
{
    controller_context_->keyPressEvents[code] = ControllerContext::KeyboardFunc_t();
    controller_context_->keyReleaseEvents[code] = ControllerContext::KeyboardFunc_t();
}