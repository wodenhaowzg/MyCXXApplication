package com.example.mycxxapplication;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import com.example.mycxxapplication.jni.BaseTest;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

/**
 * 该类主要测试 JNI 的基本数据类型传递，对象传递解析等，并保证在内存上无泄露。
 */
public class JNITransDataTest extends BaseTest {

    private static final String TAG = "JNITransDataTest";

    public JNITransDataTest(Context context) {
        super(context);
    }

    @Override
    public void startTest() {
        // 测试单个对象传递、数据解析。
//        testObject();
        // 测试对象传递、数据解析是否存在内存泄露。
//        testObjectArray();
        testTransferByteArray();
    }

    private void testTransferByteArray() {
        new Thread(() -> {
            Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.bytebuffertest);
            byte[] srcByteArray = buildSrcByteArray(bitmap);
//            YuvDataTransfer yuvDataTransfer = new YuvDataTransfer();
//            while (true) {
//                yuvDataTransfer.start(srcByteArray, bitmap.getWidth(), bitmap.getHeight());
//                try {
//                    Thread.sleep(1000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//            }

            while (true) {
                YuvDataTransfer yuvDataTransfer = new YuvDataTransfer();
                yuvDataTransfer.start(srcByteArray, bitmap.getWidth(), bitmap.getHeight());
                yuvDataTransfer.stop();
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }

    private void testObject() {
        JNIDataBean bean = new JNIDataBean();
        bean.mName = "xiaoming";
        bean.mAge = 15;
        bean.mMoney = 10000000;
        bean.mOk = true;
        nativeTransferObjectToCXX(new JNIDataBean[]{bean});
    }

    private void testObjectArray() {
        List<JNIDataBean> beanList = new ArrayList<>();
        for (int i = 0; i < 50; ++i) {
            JNIDataBean bean = new JNIDataBean();
            bean.mName = "xiaoming" + i;
            bean.mAge = 15 + i;
            bean.mMoney = 10000000 + i;
            bean.mOk = true;
            beanList.add(bean);
        }
        JNIDataBean[] array = beanList.toArray(new JNIDataBean[0]);
        new Thread(() -> {
            int count = 10000000;
            while (count > 0) {
                count--;
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                nativeTransferObjectToCXX(array);
            }
        }).start();
    }

    private byte[] buildSrcByteArray(Bitmap bitmap) {
        int byteArraySize = bitmap.getByteCount();
        ByteBuffer byteBuffer = ByteBuffer.allocate(byteArraySize);
        bitmap.copyPixelsToBuffer(byteBuffer);
        byte[] destByteArray = new byte[byteArraySize];
        System.arraycopy(byteBuffer.array(), byteBuffer.arrayOffset(), destByteArray, 0, byteArraySize);
        return destByteArray;
    }

    /**
     * JNI 接口，传递对象数组。
     *
     * @param beanArray 对象数组。
     */
    private native void nativeTransferObjectToCXX(JNIDataBean[] beanArray);


    private void onDataReport(int data1) {
        Log.d(TAG, "onDataReport -> " + data1);
    }

    private static class JNIDataBean {

        public String mName;
        public int mAge;
        public long mMoney;
        public boolean mOk;
    }

    private static class YuvDataTransfer {

        public static final int FOURCC_NV21 = 1;
        public static final int FOURCC_NV12 = 2;
        public static final int FOURCC_RGBA = 3;
        public static final int FOURCC_ABGR = 4;
        public static final int FOURCC_I420 = 5;
        public static final int FOURCC_ARGB = 6;

        private final long mPointer;
        private final JNIYuvDataBean yuvDataBean = new JNIYuvDataBean();

        public YuvDataTransfer() {
            mPointer = nativeInitialize(this);
        }

        public void start(byte[] srcByteArray, int width, int height) {
            yuvDataBean.mPixelFormat = FOURCC_I420;
            yuvDataBean.mSrcByteArray = srcByteArray;
            byte[] destDataArray = yuvDataBean.mDestByteArray;
            if (destDataArray == null || destDataArray.length != srcByteArray.length) {
                destDataArray = new byte[srcByteArray.length];
                yuvDataBean.mDestByteArray = destDataArray;
            }
            yuvDataBean.mWidth = width;
            yuvDataBean.mHeight = height;
            int isTransformSuccess = nativeTransferObjectToCXX(mPointer, yuvDataBean);
            if (isTransformSuccess != 0) {
                Log.e(TAG, "YuvDataTransfer Failed to transform I420 to NV21 when obtain jpeg byte array. error: " + isTransformSuccess);
            } else {
                Log.i(TAG, "YuvDataTransfer Succeed in transforming byte array.");
            }
        }

        public void stop() {
            nativeUnInitialize(mPointer);
        }

        private native long nativeInitialize(YuvDataTransfer transfer);

        private native void nativeUnInitialize(long pointer);

        private native int nativeTransferObjectToCXX(long pointer, Object yuvDataBean);

        private static class JNIYuvDataBean {

            public int mPixelFormat;
            public byte[] mSrcByteArray;
            public byte[] mDestByteArray;
            public ByteBuffer mSrcDirectByteBuffer;
            public ByteBuffer mCropDirectByteBuffer;
            public ByteBuffer mDestDirectByteBuffer;
            public int mWidth;
            public int mHeight;
            public int mCropX;
            public int mCropY;
            public int mCropWidth;
            public int mCropHeight;
            public int mScaleWidth;
            public int mScaleHeight;
            public int mRotate;
            public boolean mIsMirrored;

            @Override
            public String toString() {
                return "VideoDataScaleBean{" +
                        "mYuvFormat=" + mPixelFormat +
                        ", mWidth=" + mWidth +
                        ", mHeight=" + mHeight +
                        ", mCropX=" + mCropX +
                        ", mCropY=" + mCropY +
                        ", mCropWidth=" + mCropWidth +
                        ", mCropHeight=" + mCropHeight +
                        ", mScaleWidth=" + mScaleWidth +
                        ", mScaleHeight=" + mScaleHeight +
                        ", mIsMirrored=" + mIsMirrored +
                        '}';
            }
        }
    }
}
