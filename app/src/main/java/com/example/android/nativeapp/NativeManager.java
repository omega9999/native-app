package com.example.android.nativeapp;

public class NativeManager {

    public NativeManager() {
    }


    private class TestNativeRef{
        TestNativeRef(){
            this.mNativeObjects = new long[numberOfObjects()];
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                this.mNativeObjects[index] = createNativeObject((int)(Math.random()*5000+1));
            }

        }

        public void logPrimeNumbers(){
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                logNativeObject(this.mNativeObjects[index]);
            }
        }

        @Override
        protected void finalize() throws Throwable {
            super.finalize();
            for (int index = 0 ; index < this.mNativeObjects.length; index++){
                destroyNativeObject(this.mNativeObjects[index]);
            }
        }

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

    private native long createNativeObject(final int number);
    private native void destroyNativeObject(final long reference);
    private native void logNativeObject(final long reference);



    static {
        // Used to load the 'native-lib' library on application startup.
        System.loadLibrary("native-lib");
    }

    private static final String TAG = NativeManager.class.getSimpleName();
}
