package com.example.mycxxapplication.jni;

import android.content.Context;

public class ThreadTest extends BaseTest{

   public ThreadTest(Context context) {
      super(context);
   }

   @Override
   public void startTest() {
      super.startTest();
      nativeStartTest();
   }

   private native void nativeStartTest();
}
