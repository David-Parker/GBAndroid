//
// Created by David on 10/31/2021.
//

#pragma once

#include <jni.h>
#include <GlobalDefinitions.h>
#include <IEventHandler.h>
#include <JoypadController.h>
#include <atomic>

#define TOUCH_BUTTON_A 0
#define TOUCH_BUTTON_B 1
#define TOUCH_BUTTON_UP 2
#define TOUCH_BUTTON_DOWN 3
#define TOUCH_BUTTON_LEFT 4
#define TOUCH_BUTTON_RIGHT 5
#define TOUCH_BUTTON_START 6
#define TOUCH_BUTTON_SELECT 7
#define TOUCH_BUTTON_TURBO 8

// This class is just a bridge between the native C++ and Java boundary. The actual implementation resides in Java.
class TouchEventHandler : public IEventHandler
{
private:
    JNIEnv* env;
    jobject instance;
    std::atomic_bool buttonsToggled[9] = {0};
    bool shouldQuit = false;
    int speedMultiplier = 4;

public:
    TouchEventHandler(JNIEnv* env, jobject instance)
        : env(env), instance(instance)
    {
    }

    void SetQuit(bool shouldQuit);
    void HandleInput(JoypadController* joypadController);
    bool ShouldQuit();
    int SpeedMultiplier();
    void ButtonDown(int button);
    void ButtonUp(int button);
};
