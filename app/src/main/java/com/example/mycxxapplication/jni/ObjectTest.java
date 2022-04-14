package com.example.mycxxapplication.jni;

public class ObjectTest implements TestInterface{

    @Override
    public void startTest() {
        structTest();
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    Thread.sleep(10* 000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//
//                for (int i = 0; i < 1000000000; i++) {
//                    stringTest("11111");
//                }
//                Log.e("WZGTEST", "OVER.....");
//            }
//        }).start();
    }

    private native void structTest();

    private native void stringTest(String str);
}
