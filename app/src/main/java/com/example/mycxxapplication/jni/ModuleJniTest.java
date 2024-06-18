package com.example.mycxxapplication.jni;

import android.content.Context;

public class ModuleJniTest extends BaseTest {

    public ModuleJniTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        super.startTest();
        nativeStartTest();
    }

    private native void nativeStartTest();
}
