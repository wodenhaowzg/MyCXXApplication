package com.example.mycxxapplication.jni;

import android.content.Context;

public class DesignTestJni extends BaseTest {

    public DesignTestJni(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        nativeStartTest();
    }

    private native void nativeStartTest();
}