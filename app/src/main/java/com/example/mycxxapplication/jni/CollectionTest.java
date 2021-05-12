package com.example.mycxxapplication.jni;

import android.content.Context;
import android.util.Log;

public class CollectionTest extends BaseTest {

    private static final String TAG = "WZGTEST";

    public CollectionTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
//        Log.i(TAG, "Java test");
//        // i++ 和 ++i 不影响循环遍历
//        int[] array1 = new int[]{1, 2, 3, 4, 5};
//        for (int i = 0; i < array1.length; i++) {
//            Log.i(TAG, "index: " + array1[i]);
//        }
//
//        for (int i = 0; i < array1.length; ++i) {
//            Log.i(TAG, "index: " + array1[i]);
//        }
//        arrayTest();

        vectorTest();
    }

    private native void arrayTest();

    private native void vectorTest();
}
