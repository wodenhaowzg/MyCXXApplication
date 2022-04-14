package com.example.mycxxapplication.jni;

public class PointerTest implements TestInterface {

    @Override
    public void startTest() {
        pointerTest();
    }

    private native void pointerTest();
}
