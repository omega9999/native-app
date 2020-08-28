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
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(new NativeManager().stringFromJNI());

        //new ProvaSparseArray();
    }

    @Override
    protected void onResume() {
        super.onResume();

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

        final NativeManager manager = new NativeManager();
        manager.create();
        manager.logPrimeNumbers();
        manager.destroy();
    }



    private static final String TAG = MainActivity.class.getSimpleName();
}
