package com.example.mycxxapplication.jni;

import android.content.Context;

public class StringTest extends BaseTest{

    public StringTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        stringTest();
    }

    private native void stringTest();
}
