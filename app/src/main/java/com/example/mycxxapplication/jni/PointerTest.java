package com.example.mycxxapplication.jni;

import android.content.Context;

public class PointerTest extends BaseTest{

    public PointerTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        pointerTest();
    }

    private native void pointerTest();
}
