#include <jni.h>
#include <string>
#include "GameBoy.h"
#include "BitmapGraphicsHandler.h"
#include "TouchEventHandler.h"
#include "SerialNetworkHandler.h"

static GameBoy* gameBoy;
static BitmapGraphicsHandler* graphicsHandler;
static TouchEventHandler* eventHandler;
static SerialNetworkHandler* serialHandler;

extern "C"
{
    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyInit(
            JNIEnv* env,
            jobject instance,
            jstring romFolder,
            jobjectArray error)
    {
        jboolean isCopy;

        graphicsHandler = new BitmapGraphicsHandler();
        eventHandler = new TouchEventHandler(env, instance);
        serialHandler = new SerialNetworkHandler();

        try
        {
            gameBoy = new GameBoy(
                env->GetStringUTFChars(romFolder, &isCopy),
                graphicsHandler,
                eventHandler,
                serialHandler);
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyDestroy(
            JNIEnv* env,
            jobject instance)
    {
        delete gameBoy;
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyLoadRom(
            JNIEnv* env,
            jobject instance,
            jstring romName,
            jobjectArray error)
    {
        jboolean isCopy;

        try
        {
            gameBoy->LoadRom(
                    env->GetStringUTFChars(romName, &isCopy));
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT jboolean JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyShouldStop(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            return gameBoy->ShouldStop();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
            return true;
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyStart(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            gameBoy->Start();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyStop(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            gameBoy->Stop();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyStep(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            gameBoy->Step();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyRun(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            graphicsHandler->SetJNIVariables(env, instance);
            gameBoy->Run();
            eventHandler->SetQuit(false);
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoySaveGame(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            gameBoy->SaveGame();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT jlong JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoyFramesElapsed(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            return gameBoy->FramesElapsed();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
            return 0;
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_gameBoySimulateFrameDelay(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            gameBoy->SimulateFrameDelay();
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_buttonDownEvent(
            JNIEnv* env,
            jobject instance,
            int button,
            jobjectArray error)
    {
        try
        {
            eventHandler->ButtonDown(button);
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_buttonUpEvent(
            JNIEnv* env,
            jobject instance,
            int button,
            jobjectArray error)
    {
        try
        {
            eventHandler->ButtonUp(button);
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_gbandroid_BitmapActivity_pauseGameBoy(
            JNIEnv* env,
            jobject instance,
            jobjectArray error)
    {
        try
        {
            eventHandler->SetQuit(true);
        }
        catch (std::exception& ex)
        {
            env->SetObjectArrayElement(error, 0, env->NewStringUTF(ex.what()));
        }
    }
}