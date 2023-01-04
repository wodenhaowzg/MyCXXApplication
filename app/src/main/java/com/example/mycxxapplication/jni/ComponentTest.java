package com.example.mycxxapplication.jni;

import android.os.SystemClock;

import com.example.mycxxapplication.utils.LogUtils;

public class ComponentTest implements TestInterface {

    @Override
    public void startTest() {
        testTimeComponent();
    }

    private void testTimeComponent() {
        LogUtils.logI("Java System.currentTimeMillis = " + System.currentTimeMillis());
        LogUtils.logI("Java System.nanoTime = " + System.nanoTime());
        LogUtils.logI("Java SystemClock.uptimeMillis = " + SystemClock.uptimeMillis());
        nativeTestTimeComponent();
    }

    private native void nativeTestTimeComponent();

    private native void testComponent();
}
