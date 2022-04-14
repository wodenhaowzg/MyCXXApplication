package com.example.mycxxapplication.jni;

public class StringTest implements TestInterface {

    @Override
    public void startTest() {
        stringTest();
    }

    private native void stringTest();
}
