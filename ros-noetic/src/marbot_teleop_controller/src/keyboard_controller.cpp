#include "marbot_teleop_controller/keyboard_controller.h"
#include "marbot_teleop_controller/controller_context.h"

// https://codereview.stackexchange.com/questions/93488/c-keyboard-controller

Controller::Controller()
    : controller_context_(new ControllerContext())
{
}

bool Controller::OnKeyPress(const SDL_Event &e)
{
    const auto & scancode = e.key.keysym.scancode;

    const auto & pressFuncs = controller_context_->keyPressEvents[scancode];

    bool ret_flag = false;

    if (pressFuncs.size())
    {
        // Call callback if valid
        for (auto &func : pressFuncs) {
            func();
        }
        ret_flag = true;
    }

    if (!controller_context_->pressed[scancode])
    {
        const auto & pressOnceFuncs = controller_context_->keyPressOnceEvents[scancode];

        if (pressOnceFuncs.size())
        {
            // Call callback if valid
            for (auto &func : pressOnceFuncs) {
                func();
            }
            ret_flag = true;
        }
    }

    controller_context_->pressed[scancode] = true;

    return ret_flag;
}

bool Controller::OnKeyRelease(const SDL_Event &e)
{
    const auto & scancode = e.key.keysym.scancode;

    const auto & releaseFuncs = controller_context_->keyReleaseEvents[scancode];

    bool ret_flag = false;

    if (releaseFuncs.size())
    {
        // Call callback if valid
        for (auto &func : releaseFuncs) {
            func();
        }
        ret_flag = true;
    }

    controller_context_->pressed[scancode] = false;

    return ret_flag;
}

void Controller::SetReleaseCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t &func)
{
    controller_context_->keyReleaseEvents[code].push_back(func); 
}

void Controller::SetPressCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t &func)
{
    controller_context_->keyPressEvents[code].push_back(func);
}

void Controller::SetPressOnceCallback(SDL_Scancode code, const ControllerContext::KeyboardFunc_t & func)
{
    controller_context_->keyPressOnceEvents[code].push_back(func);
}

void Controller::ClearCallbacks(SDL_Scancode code)
{
    // One-to-one mapping clear
    // controller_context_->keyPressEvents[code] = ControllerContext::KeyboardFunc_t();
    // controller_context_->keyReleaseEvents[code] = ControllerContext::KeyboardFunc_t();

    controller_context_->keyPressEvents[code].clear();
    controller_context_->keyReleaseEvents[code].clear();
}
