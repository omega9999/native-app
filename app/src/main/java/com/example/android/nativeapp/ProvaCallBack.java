package com.example.android.nativeapp;

import javax.annotation.Nullable;

public class ProvaCallBack {
    public ProvaCallBack() {
        //CallBackContainer.addListener(null); //ERROR
        CallBackContainer.addListener(msg -> {

        });
        CallBackContainer.addListener((msg, msg2) -> {

        });
    }
}
