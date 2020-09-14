package com.example.android.nativeapp;

import androidx.annotation.NonNull;

import java.util.ArrayList;
import java.util.List;

import javax.annotation.Nullable;

public class CallBackContainer {

    private CallBackContainer(@Nullable CallBackGeneric callBack) {
        this.mCallBack = callBack;
    }

    public static void addListener(@Nullable CallBackSimple callBack){
        innerAddListener(callBack);
    }
    public static void addListener(@Nullable CallBackDouble callBack){
        innerAddListener(callBack);
    }


    private static void innerAddListener(@Nullable CallBackGeneric callBack){
        CONTAINER.add(new CallBackContainer(callBack));
    }



    private void callback(@Nullable final String msg, @NonNull final ErrorInfo msg2){
        if (this.mCallBack != null){
            if (this.mCallBack instanceof CallBackSimple){
                ((CallBackSimple)this.mCallBack).callback(msg);
            }
            else if (this.mCallBack instanceof CallBackDouble){
                ((CallBackDouble)this.mCallBack).callback(msg, msg2);
            }
            else{
                Log.v(TAG,"???");
            }
        }
    }



    static class ErrorInfo{
        private String msg;
        private ErrorType type;

    }
    enum ErrorType{

    }

    interface CallBackGeneric{

    }

    @SuppressWarnings("DeprecatedIsStillUsed")
    @Deprecated
    interface CallBackSimple extends CallBackGeneric{
        void callback(@Nullable final String msg);
    }

    interface CallBackDouble extends CallBackGeneric{
        void callback(@Nullable final String msg, @Nullable final ErrorInfo msg2);
    }

    private final CallBackGeneric mCallBack;
    private static List<CallBackContainer> CONTAINER = new ArrayList<>();
    private static final String TAG = CallBackContainer.class.getSimpleName();
}
