//
// Created by David on 10/31/2021.
//

#pragma once

#include <jni.h>
#include <GlobalDefinitions.h>
#include <IGraphicsHandler.h>

// This class is just a bridge between the native C++ and Java boundary. The actual implementation resides in Java.
class BitmapGraphicsHandler : public IGraphicsHandler
{
private:
    JNIEnv* env;
    jobject instance;
    jclass instanceClass;

public:
    BitmapGraphicsHandler()
    {
    }

    void SetJNIVariables(JNIEnv* env, jobject instance);
    void Init();
    void Clear();
    void Draw(const u32* pixelBuffer, int width, int height);
    void Quit();
};