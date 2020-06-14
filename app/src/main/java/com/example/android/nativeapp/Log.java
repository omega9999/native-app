package com.example.android.nativeapp;

import androidx.annotation.NonNull;

public class Log {
    public static void v(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.v(tag, String.format(message,args));
    }
    public static void d(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.d(tag, String.format(message,args));
    }
    public static void i(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.i(tag, String.format(message,args));
    }
    public static void w(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.w(tag, String.format(message,args));
    }
    public static void e(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.e(tag, String.format(message,args));
    }
    public static void wtf(@NonNull final String tag, @NonNull final String message, Object... args){
        android.util.Log.wtf(tag, String.format(message,args));
    }
}
