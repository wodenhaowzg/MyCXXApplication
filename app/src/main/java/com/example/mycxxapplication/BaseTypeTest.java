package com.example.mycxxapplication;

import android.content.Context;

import com.example.mycxxapplication.jni.BaseTest;

public class BaseTypeTest extends BaseTest {

    public BaseTypeTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        printBaseType();
    }

    private native void printBaseType();
}
