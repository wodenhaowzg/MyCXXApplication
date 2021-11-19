package com.example.mycxxapplication.jni;

import android.content.Context;

public class ObjectTest extends BaseTest{

    public ObjectTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        structTest();
    }

    private native void structTest();
}
