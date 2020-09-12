package com.example.android.nativeapp;

public class TestSize {
    private static int SAMPLE_SIZE = 100;
    private static long SLEEP_INTERVAL = 100;

    private void test(){

        long startMemoryUse = getMemoryUse();
        //TODO create object
        long endMemoryUse = getMemoryUse();
        //TODO endMemoryUse - startMemoryUse
    }

    private long getMemoryUse(){
        putOutTheGarbage();
        long totalMemory = Runtime.getRuntime().totalMemory();
        putOutTheGarbage();
        long freeMemory = Runtime.getRuntime().freeMemory();
        return (totalMemory - freeMemory);
    }

    private void putOutTheGarbage() {
        collectGarbage();
        collectGarbage();
    }

    private void collectGarbage() {
        try {
            System.gc();
            Thread.currentThread().sleep(SLEEP_INTERVAL);
            System.runFinalization();
            Thread.currentThread().sleep(SLEEP_INTERVAL);
        }
        catch (InterruptedException ex){
            ex.printStackTrace();
        }
    }
}
