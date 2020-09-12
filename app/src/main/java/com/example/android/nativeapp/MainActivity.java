package com.example.android.nativeapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Looper;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text1);
        tv.setText(new NativeManager().stringFromJNI());

        //new ProvaSparseArray();

        Log.v(TAG,"Number of cores %1$s", nativeManager1.getNumberOfCores());
        Log.v(TAG,"BuildVersion %1$s", NativeManager.getBuildVersion());
        Log.v(TAG,"BuildVersion %1$s", NativeManager.getRuntimeMemorySize());
    }


    @Override
    protected void onResume() {
        super.onResume();
        TextView tv1 = findViewById(R.id.sample_text1);
        nativeManager1.addListenerValue(value -> runOnUiThread(() -> tv1.setText(tv1.getText() + "\n"+value)));
        nativeManager1.startTest("manager 1");

        TextView tv2 = findViewById(R.id.sample_text2);
        nativeManager2.addListenerValue(value -> runOnUiThread(() -> tv2.setText(tv2.getText() + "\n"+value)));
        nativeManager2.startTest("manager 2");

        //check main thread java
        Log.v(TAG, "is Main Thread ? %1$s",(Looper.myLooper() == Looper.getMainLooper()));

        /*
        int no = Integer.parseInt(new NativeManager().stringNumber());
        if (new NativeManager().isPrime(no)) {
            Toast.makeText(this, "Prime Number: " + no, Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Not Prime Number: " + no, Toast.LENGTH_SHORT).show();
        }

         */

        /*
        final NativeManager manager = new NativeManager();
        manager.createTest();
        manager.logPrimeNumbers();
        manager.destroyTest();

         */

    }

    @Override
    protected void onPause() {
        super.onPause();
        nativeManager1.removeListenerValue();
        nativeManager1.destroy();

        nativeManager2.removeListenerValue();
        nativeManager2.destroy();
    }



    private NativeManager nativeManager1 = new NativeManager();
    private NativeManager nativeManager2 = new NativeManager();

    private static final String TAG = MainActivity.class.getSimpleName();
}
