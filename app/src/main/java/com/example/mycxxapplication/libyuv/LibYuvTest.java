package com.example.mycxxapplication.libyuv;

import android.content.Context;

import com.example.mycxxapplication.jni.BaseTest;

public class LibYuvTest extends BaseTest {

    public static final int PIXEL_FORMAT_I420 = 1;
    public static final int PIXEL_FORMAT_ABGR = 2;

    private long mPointer;

    public LibYuvTest(Context context) {
        super(context);
    }

    public void initialize() {
        if (mPointer != 0) {
            return;
        }
        mPointer = nativeInitialize();
    }

    public void unInitialize() {
        if (mPointer == 0) {
            return;
        }
        nativeUnInitialize(mPointer);
    }

    public int transformPixelFormatAndAttributes(JNIPixelFormatBean jniPixelFormatBean) {
        if (mPointer == 0) {
            return -1;
        }
        return nativeTransferToABGR(mPointer, jniPixelFormatBean, null);
    }

    public int transformPixelFormatAndAttributes(JNIPixelFormatBean jniPixelFormatBean, JNIPixelOptionBean jniPixelOptionBean) {
        if (mPointer == 0) {
            return -1;
        }
        return nativeTransferToABGR(mPointer, jniPixelFormatBean, jniPixelOptionBean);
    }

    private native long nativeInitialize();

    private native long nativeUnInitialize(long pointer);

    private native int nativeTransferToABGR(long pointer, Object jniPixelFormatBean, Object jniPixelOptionBean);

}
