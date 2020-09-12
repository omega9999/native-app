package com.example.android.nativeapp;


import android.annotation.SuppressLint;
import android.os.Build;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.io.File;
import java.io.FileFilter;
import java.util.Hashtable;
import java.util.Map;
import java.util.UUID;
import java.util.regex.Pattern;

public class NativeManager {

    public interface ListenerValue {
        void callBack(@Nullable final String value);
    }

    /*
    identificativo oggetti (anche dimensione)

    System.identityHashCode(object) (hash code di object != indirizzo di memoria)
    https://github.com/eugenp/tutorials/tree/master/core-java-modules/core-java-jvm-2

    https://openjdk.java.net/projects/code-tools/jol/
    implementation "org.openjdk.jol:jol-core:0.10"
    */
    public NativeManager() {
        Log.v(TAG, "object hash code %s", System.identityHashCode(this));
        this.mIdentifier = UUID.randomUUID().toString();
        synchronized (NativeManager.class) {
            DEFINITION_MAP.put(this.mIdentifier, this);
            initObject(this.mIdentifier);
        }
        reference = new TestNativeRef();
    }

    public void startTest(@NonNull final String str) {
        checkStatus();
        new Thread() {
            @Override
            public void run() {
                startTimer(mIdentifier, 4000, str + " messaggio di prova thread java", false);
            }
        }.start();
        startTimer(mIdentifier, 6000, str + " messaggio di prova thread c++", true);
    }

    public synchronized void destroy() {
        Log.v(TAG, "destroy");
        if (!mIsDestroyed) {
            synchronized (NativeManager.class) {
                destroyObject(this.mIdentifier);
                DEFINITION_MAP.remove(this.mIdentifier);
            }
            mIsDestroyed = true;
        }
    }

    private void checkStatus(){
        if (mIsDestroyed){
            throw new RuntimeException(String.format("%1$s with id %2$s not usable because destroyed", this.getClass().getSimpleName(), mIdentifier));
        }
    }

    public synchronized void addListenerValue(@NonNull final ListenerValue listener) {
        checkStatus();
        this.mListenerValue = listener;
    }

    public synchronized void removeListenerValue() {
        this.mListenerValue = null;
    }

    @SuppressWarnings({"unused", "RedundantSuppression"})
    @Keep
    private static void callBack(@NonNull final String id, @Nullable final String value) {
        Log.v(TAG, "java callback %s %s", id, value);
        NativeManager manager;
        synchronized (NativeManager.class) {
            manager = DEFINITION_MAP.get(id);
        }
        if (manager != null && !manager.mIsDestroyed) {
            if (manager.mListenerValue != null) {
                manager.mListenerValue.callBack(value);
            }
        }
    }

    private native void initObject(final String identifier);

    private native void destroyObject(final String identifier);

    private static native void startTimer(final String identifier, final long timeMillis, @NonNull final String msg, boolean async);

    @Override
    protected void finalize() throws Throwable {
        destroy();
        super.finalize();
    }

    /*
     * Return OS build version: a static function
     */
    @Keep
    public static String getBuildVersion() {
        return Build.VERSION.RELEASE;
    }

    /*
     * Return Java memory info
     */
    @Keep
    public static long getRuntimeMemorySize() {
        return Runtime.getRuntime().freeMemory();
    }

    @SuppressLint("ObsoleteSdkInt")
    public int getNumberOfCores() {
        if (Build.VERSION.SDK_INT >= 17) {
            Log.v(TAG, "Runtime.getRuntime().availableProcessors()");
            return Runtime.getRuntime().availableProcessors();
        } else {
            // Use saurabh64's answer
            Log.v(TAG, "getNumCoresOldPhones()");
            return getNumCoresOldPhones();
        }
    }

    /**
     * Gets the number of cores available in this device, across all processors.
     * Requires: Ability to peruse the filesystem at "/sys/devices/system/cpu"
     *
     * @return The number of cores, or 1 if failed to get result
     */
    private int getNumCoresOldPhones() {
        //Private Class to display only CPU devices in the directory listing
        class CpuFilter implements FileFilter {
            @Override
            public boolean accept(File pathname) {
                //Check if filename is "cpu", followed by a single digit number
                if (Pattern.matches("cpu[0-9]+", pathname.getName())) {
                    return true;
                }
                return false;
            }
        }

        try {
            //Get directory containing CPU info
            File dir = new File("/sys/devices/system/cpu/");
            //Filter to only list the devices we care about
            File[] files = dir.listFiles(new CpuFilter());
            //Return the number of cores (virtual CPU devices)
            return files != null ? files.length : 1;
        } catch (Exception e) {
            //Default to return 1 core
            return 1;
        }
    }

    public void createTest() {
        reference.create();
    }


    public void logPrimeNumbers() {
        reference.logPrimeNumbers();
    }

    public void destroyTest() {
        reference.close();
        reference = null;
    }


    private class TestNativeRef {
        TestNativeRef() {
            this.mNativeObjects = new long[numberOfObjects()];
        }

        public void create() {
            Log.v(TAG, "PrimeNumber create %1$s", this.mNativeObjects.length);
            for (int index = 0; index < this.mNativeObjects.length; index++) {
                this.mNativeObjects[index] = createNativeObject((int) (Math.random() * 5000 + 1));
            }

        }

        public void logPrimeNumbers() {
            Log.v(TAG, "PrimeNumber logs %1$s", this.mNativeObjects.length);
            for (int index = 0; index < this.mNativeObjects.length; index++) {
                logNativeObject(this.mNativeObjects[index]);
            }
        }

        public synchronized void close() {
            Log.v(TAG, "PrimeNumber close");
            for (int index = 0; index < this.mNativeObjects.length; index++) {
                destroyNativeObject(this.mNativeObjects[index]);
            }
            isClosed = true;
        }

        @Override
        protected void finalize() throws Throwable {
            Log.v(TAG, "PrimeNumber finalize");
            if (!isClosed) {
                close();
            }
            super.finalize();
        }

        private boolean isClosed = false;
        private final long mNativeObjects[];
    }

    public native long getSize(Object o);

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String stringNumber();

    public native boolean isPrime(int t);


    private native int numberOfObjects();

    private static native long createNativeObject(final int number);

    private static native void destroyNativeObject(final long reference);

    private static native void logNativeObject(final long reference);


    private TestNativeRef reference;

    private final String mIdentifier;
    private boolean mIsDestroyed = false;
    private ListenerValue mListenerValue;

    private static long COUNTER = 0;
    private static final Map<String, NativeManager> DEFINITION_MAP = new Hashtable<>();


    static {
        // Used to load the 'native-lib' library on application startup.
        System.loadLibrary("native-lib");
    }

    private static final String TAG = NativeManager.class.getSimpleName();
}
