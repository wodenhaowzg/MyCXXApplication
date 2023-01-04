package com.example.mycxxapplication.jni;

public class StringTest implements TestInterface {

    @Override
    public void startTest() {
        stringTest();

        String [] testString = new String[1000];
        for (int i = 0; i < 1000; i++) {
            testString[i] = "111111111111111111111111111111111111111111111111";
        }


        new Thread(() -> {
            while (true) {
                try {
                    Thread.sleep(20);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                nativeTransCopyString(testString);
            }
        }).start();
    }

    private native void stringTest();

    private native void nativeTransCopyString(String[] stringArray);
}
