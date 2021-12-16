package com.example.gbandroid;

import android.app.Activity;
import android.content.res.AssetManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

// Deploys all files in the APK's assets directory to the app's scoped external storage directory.
// Note: AssetManager ignores empty directories, and therefore they will not be deployed.
public class AssetDeployer {

    private final AssetManager assetManager;
    private final String externalStorage;

    public AssetDeployer(Activity activity)
    {
        this.assetManager = activity.getAssets();
        this.externalStorage = activity.getExternalFilesDirs(null)[0].getAbsolutePath();
    }

    public void DeployAssets() throws IOException
    {
        copyFileOrDirectory("");
    }

    private void copyFileOrDirectory(String path) throws IOException
    {
        if (this.assetManager.list(path).length == 0)
        {
            // This path is to a file, copy it to external storage.
            copyFile(path);
        }
        else
        {
            // This path is to a sub-directory, recursively copy all files and sub-directories.
            createDirIfNotExists(this.externalStorage + "/" + path);

            // Copy Assets sub-directory from APK to app's external equivalent directory.
            String[] assetPaths = this.assetManager.list(path);

            for (String relPath : assetPaths)
            {
                if (path == "")
                {
                    copyFileOrDirectory(relPath);
                }
                else
                {
                    copyFileOrDirectory(path + "/" + relPath);
                }
            }
        }
    }

    // Copy a file from assets to external storage.
    private void copyFile(String path) throws IOException
    {
        String externalDest = this.externalStorage + "/" + path;
        InputStream in = this.assetManager.open(path);
        OutputStream out = new FileOutputStream(externalDest);
        byte[] buffer = new byte[1024];
        int read = 0;

        while ((read = in.read(buffer)) != -1)
        {
            out.write(buffer, 0, read);
        }

        out.flush();
        in.close();
        out.close();
    }

    // Creates a directory, if it doesn't exist.
    private void createDirIfNotExists(String path) throws IOException
    {
        File dir = new File(path);

        if (dir.exists())
        {
            if (!dir.isDirectory())
            {
                throw new IOException("Can't create directory, a file with the name already exists.");
            }
        }
        else
        {
            dir.mkdirs();

            if (!dir.isDirectory())
            {
                throw new IOException("Unable to create directory.");
            }
        }
    }
}