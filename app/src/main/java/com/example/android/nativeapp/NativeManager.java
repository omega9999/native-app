package com.example.android.nativeapp;

public class NativeManager {


    public NativeManager() {
        reference = new TestNativeRef();
    }

    public void create() {
        reference.create();
    }


    public void logPrimeNumbers() {
        reference.logPrimeNumbers();
    }

    public void destroy(){
        reference.close();
        reference = null;
    }


    private class TestNativeRef{
        TestNativeRef(){
            this.mNativeObjects = new long[numberOfObjects()];
        }

        public void create(){
            Log.v(TAG,"PrimeNumber create %1$s",this.mNativeObjects.length);
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                this.mNativeObjects[index] = createNativeObject((int)(Math.random()*5000+1));
            }

        }

        public void logPrimeNumbers(){
            Log.v(TAG,"PrimeNumber logs %1$s",this.mNativeObjects.length);
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                logNativeObject(this.mNativeObjects[index]);
            }
        }

        public synchronized void close() {
            Log.v(TAG,"PrimeNumber close");
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                destroyNativeObject(this.mNativeObjects[index]);
            }
            isClosed = true;
        }

        @Override
        protected void finalize() throws Throwable {
            Log.v(TAG,"PrimeNumber finalize");
            if (!isClosed){
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

    static {
        // Used to load the 'native-lib' library on application startup.
        System.loadLibrary("native-lib");
    }

    private static final String TAG = NativeManager.class.getSimpleName();
}
