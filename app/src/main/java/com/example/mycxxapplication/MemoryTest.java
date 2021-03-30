package com.example.mycxxapplication;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import java.nio.ByteBuffer;

/**
 * 测试C++内存释放
 * 得出结论1：删除结构体对象时，一定要注意内部是否存在有指针，如果有需要调用 free 来释放。
 */
public class MemoryTest extends BaseTest {

    private byte[] mBitmapData;
    private int mWidth, mHeight;

    public MemoryTest(Context context) {
        super(context);
    }

    public void startTest() {
        Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.bytebuffertest);
        mWidth = bitmap.getWidth();
        mHeight = bitmap.getHeight();
        ByteBuffer byteBuffer = ByteBuffer.allocate(bitmap.getByteCount());
        bitmap.copyPixelsToBuffer(byteBuffer);
        mBitmapData = byteBuffer.array();

        new Thread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < 1000; i++) {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    Log.d("wzgtest", "testFreeData...");
                    testFreeData(mBitmapData, mBitmapData.length, mWidth, mHeight);
                }
            }
        }).start();
    }

    private native void testFreeData(byte[] buf, int len, int width, int height);
}
