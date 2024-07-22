package com.example.mycxxapplication.jni;

import android.content.Context;

public class ThreadTest extends BaseTest{

   public ThreadTest(Context context) {
      super(context);
   }

   @Override
   public void startTest() {
      super.startTest();
//      nativeStartTest();

      webrtcThreadTest();

      new Thread(new Runnable() {
         @Override
         public void run() {
            try {
               Thread.sleep(5000);
            } catch (InterruptedException e) {
               throw new RuntimeException(e);
            }
            webrtcThreadStopTest();
//            webrtcThreadTest();
         }
      }).start();
   }

   private native void nativeStartTest();

   private native void webrtcThreadTest();

   private native void webrtcThreadStopTest();
}
