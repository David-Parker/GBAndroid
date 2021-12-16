package com.example.gbandroid;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.gbandroid.databinding.ActivityMainBinding;

import java.io.IOException;
import java.nio.Buffer;
import java.nio.IntBuffer;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicIntegerArray;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.ReentrantLock;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class BitmapActivity extends AppCompatActivity {

    private static String LogTag = "GBAndroid";
    private static boolean init = false;

    private ImageView screen;
    private Bitmap screenBitmap;
    private AtomicBoolean blue = new AtomicBoolean(false);
    private int[] buffer = new int[160 * 144];
    private AtomicReference<int[]> pixelBuffer = new AtomicReference<int[]>(buffer);
    private Timer timer;

    private final int buttonACode = 0;
    private final int buttonBCode = 1;
    private final int buttonUpCode = 2;
    private final int buttonDownCode = 3;
    private final int buttonLeftCode = 4;
    private final int buttonRightCode = 5;
    private final int buttonStartCode = 6;
    private final int buttonSelectCode = 7;
    private final int buttonTurboCode = 8;

    // Used to load the 'myapplication' library on application startup.
    static {
        System.loadLibrary("gbandroid");
    }

    public void DrawBitmap(int[] arr)
    {
        pixelBuffer.set(arr);
    }

    public void RegisterButtons()
    {
        // Set A button listener
        Button buttonA = (Button) findViewById(R.id.button_A);
        Button buttonB = (Button) findViewById(R.id.button_B);
        Button buttonUp = (Button) findViewById(R.id.button_up);
        Button buttonDown = (Button) findViewById(R.id.button_down);
        Button buttonLeft = (Button) findViewById(R.id.button_left);
        Button buttonRight = (Button) findViewById(R.id.button_right);
        Button buttonStart = (Button) findViewById(R.id.button_start);
        Button buttonSelect = (Button) findViewById(R.id.button_select);
        Button buttonTurbo = (Button) findViewById(R.id.button_turbo);

        buttonA.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonACode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonACode, error);
            }

            return true;
        });

        buttonB.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonBCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonBCode, error);
            }

            return true;
        });

        buttonUp.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonUpCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonUpCode, error);
            }

            return true;
        });

        buttonDown.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonDownCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonDownCode, error);
            }

            return true;
        });

        buttonLeft.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonLeftCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonLeftCode, error);
            }

            return true;
        });

        buttonRight.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonRightCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonRightCode, error);
            }

            return true;
        });

        buttonStart.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonStartCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonStartCode, error);
            }

            return true;
        });

        buttonSelect.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonSelectCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonSelectCode, error);
            }

            return true;
        });

        buttonTurbo.setOnTouchListener((v, event) -> {
            String[] error = new String[1];
            error[0] = null;

            if (event.getAction() == MotionEvent.ACTION_DOWN)
            {
                buttonDownEvent(buttonTurboCode, error);
            }
            else if (event.getAction() == MotionEvent.ACTION_UP)
            {
                buttonUpEvent(buttonTurboCode, error);
            }

            return true;
        });
    }

    @Override
    public void onResume()
    {
        super.onResume();

        timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        screenBitmap.setPixels(pixelBuffer.get(), 0 ,screenBitmap.getWidth() , 0, 0, screenBitmap.getWidth(), screenBitmap.getHeight());
                        screen.setImageBitmap(screenBitmap);
                    }
                });
            }
        }, 0, 17);

        new Thread(new Runnable()
        { @Override
        public void run()
        {
            // Initialize the GameBoy emulator
            String[] error = new String[1];
            error[0] = null;

            if (init == false)
            {
                init = true;
                gameBoyInit(getExternalFilesDirs(null)[0].getAbsolutePath() + "/rom", error);

                if (error[0] != null)
                {
                    Log.e(LogTag, error[0]);
                    return;
                }

                gameBoyLoadRom("Pokemon.gb", error);

                if (error[0] != null)
                {
                    Log.e(LogTag, error[0]);
                    return;
                }

                gameBoyStart(error);

                if (error[0] != null)
                {
                    Log.e(LogTag, error[0]);
                    return;
                }
            }

            gameBoyRun(error);

            if (error[0] != null)
            {
                Log.e(LogTag, error[0]);
                return;
            }

            Log.d(LogTag, "Ending previous GameBoy.");
        }
        }).start();
    }

    @Override
    public void onPause()
    {
        super.onPause();
        String[] error = new String[1];
        error[0] = null;

        timer.cancel();
        pauseGameBoy(error);
        Log.d(LogTag, "Paused GameBoy.");
        gameBoySaveGame(error);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RegisterButtons();
        getSupportActionBar().hide();

        screenBitmap = Bitmap.createBitmap(160, 144, Bitmap.Config.ARGB_8888);
        screenBitmap.eraseColor(Color.RED);

        screen = (ImageView)findViewById(R.id.imageView);
        screen.setImageBitmap(screenBitmap);

        try
        {
            AssetDeployer assetDeployer = new AssetDeployer(this);
            assetDeployer.DeployAssets();
        }
        catch (IOException ex)
        {
            Log.e(LogTag, ex.toString());
        }
    }

    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    public native void gameBoyInit(String romFolder, String[] err);
    public native void gameBoyDestroy();
    public native void gameBoyLoadRom(String romName, String[] err);
    public native boolean gameBoyShouldStop(String[] err);
    public native void gameBoyStart(String[] err);
    public native void gameBoyStop(String[] err);
    public native void gameBoyStep(String[] err);
    public native void gameBoyRun(String[] err);
    public native void gameBoySaveGame(String[] err);
    public native long gameBoyFramesElapsed(String[] err);
    public native void gameBoySimulateFrameDelay(String[] err);
    public native void buttonDownEvent(int button, String[] err);
    public native void buttonUpEvent(int button, String[] err);
    public native void pauseGameBoy(String[] err);
}