package com.example.mycxxapplication.jni;

import android.content.Context;

import java.nio.ByteBuffer;

public abstract class BaseTest {

    protected Context mContext;

    public BaseTest(Context context) {
        this.mContext = context;
    }

    public abstract void startTest();
}
