package com.example.android.nativeapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(new NativeManager().stringFromJNI());
    }

    @Override
    protected void onResume() {
        super.onResume();

        int no = Integer.parseInt(new NativeManager().stringNumber());
        if (new NativeManager().isPrime(no)) {
            Toast.makeText(this, "Prime Number: " + no, Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Not Prime Number: " + no, Toast.LENGTH_SHORT).show();
        }
    }
}
