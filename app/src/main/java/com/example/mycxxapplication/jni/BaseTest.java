package com.example.mycxxapplication.jni;

import android.content.Context;

public class BaseTest implements TestInterface {

    protected Context mContext;

    public BaseTest(Context context) {
        this.mContext = context;
    }

    @Override
    public void startTest() {
//        nativeStartTest();
        nativeConstTest();
    }

    private native void nativeStartTest();

    private native void nativeConstTest();
}
