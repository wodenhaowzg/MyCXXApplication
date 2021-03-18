package com.example.mycxxapplication;

import android.content.Context;
import android.util.Log;

import java.nio.ByteBuffer;

class JNITransDataTest extends BaseTest {

    private static final String TAG = "JNITransDataTest";

    public JNITransDataTest(Context context) {
        super(context);
    }

    private native void getDataFromCxx();

    private void onDataReport(int data1) {
        Log.d(TAG, "onDataReport -> " + data1);
    }
}
