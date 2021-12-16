//
// Created by David on 10/31/2021.
//

#include "BitmapGraphicsHandler.h"

void BitmapGraphicsHandler::SetJNIVariables(JNIEnv* env, jobject instance)
{
    this->env = env;
    this->instance = instance;
    this->instanceClass = env->GetObjectClass(instance);
}

void BitmapGraphicsHandler::Init()
{

}

void BitmapGraphicsHandler::Clear()
{

}

void BitmapGraphicsHandler::Draw(const u32* pixelBuffer, int width, int height)
{
    jintArray arr = env->NewIntArray(width * height);
    env->SetIntArrayRegion(arr, 0, width * height, (jint*)pixelBuffer);
    jclass mainActivity = env->GetObjectClass(instance);
    jmethodID drawBitmap = env->GetMethodID(mainActivity, "DrawBitmap", "([I)V");
    env->CallVoidMethod(instance, drawBitmap, arr);
    env->DeleteLocalRef(arr);
    env->DeleteLocalRef(mainActivity);
}

void BitmapGraphicsHandler::Quit()
{

}