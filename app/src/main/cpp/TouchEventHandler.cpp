//
// Created by David on 10/31/2021.
//

#include "TouchEventHandler.h"

void TouchEventHandler::SetQuit(bool shouldQuit)
{
    this->shouldQuit = shouldQuit;
}

void TouchEventHandler::HandleInput(JoypadController* joypadController)
{
    if (this->buttonsToggled[TOUCH_BUTTON_A])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_A);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_A);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_B])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_B);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_B);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_UP])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_UP);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_UP);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_DOWN])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_DOWN);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_DOWN);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_LEFT])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_LEFT);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_LEFT);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_RIGHT])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_RIGHT);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_RIGHT);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_START])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_START);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_START);
    }

    if (this->buttonsToggled[TOUCH_BUTTON_SELECT])
    {
        joypadController->KeyDown(JOYPAD_BUTTONS::BUTTON_SELECT);
    }
    else
    {
        joypadController->KeyUp(JOYPAD_BUTTONS::BUTTON_SELECT);
    }
    if (this->buttonsToggled[TOUCH_BUTTON_TURBO])
    {
        this->speedMultiplier = 12;
    }
    else
    {
        this->speedMultiplier = 4;
    }
}

bool TouchEventHandler::ShouldQuit()
{
    return this->shouldQuit;
}

int TouchEventHandler::SpeedMultiplier()
{
    return this->speedMultiplier;
}

void TouchEventHandler::ButtonDown(int button) {
    this->buttonsToggled[button] = true;
}

void TouchEventHandler::ButtonUp(int button) {
    this->buttonsToggled[button] = false;
}