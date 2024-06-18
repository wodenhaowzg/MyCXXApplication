package com.example.mycxxapplication.jni;

import android.content.Context;

public class LogTestJni extends BaseTest {

    public LogTestJni(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        nativeStartTest();
    }

    private native void nativeStartTest();
}
