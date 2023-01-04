package com.example.mycxxapplication.ui;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.databinding.DataBindingUtil;

import com.example.mycxxapplication.R;
import com.example.mycxxapplication.databinding.ActivityLibyuvTestBinding;
import com.example.mycxxapplication.libyuv.JNIPixelFormatBean;
import com.example.mycxxapplication.libyuv.JNIPixelOptionBean;
import com.example.mycxxapplication.libyuv.LibYuvTest;

import java.nio.ByteBuffer;

public class LibYuvTestActivity extends BaseActivity {

    private static final String TAG = LibYuvTestActivity.class.getSimpleName();
    private ActivityLibyuvTestBinding mViewBinding;
    private boolean mIsBigImage;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mViewBinding = DataBindingUtil.setContentView(this, R.layout.activity_libyuv_test);
//        testMemoryLeak(); // 测试频繁创建/销毁 libyuv 封装对象，是否存在内存泄露
//        testSrcDataLenChanged(); // 测试不同分辨率之间切换
        testCropScale(); // 测试 libyuv 裁剪、缩放
    }

    private int mTestCount = 0;
    private int mTotalElapsed;
    private boolean mIsMirror;

    private void testMemoryLeak() {
        new Thread(() -> {
            while (true) {
                runOnUiThread(() -> {
                    LibYuvTest libYuvTest = new LibYuvTest(mContext);
                    libYuvTest.initialize();
                    PixelBufferBean pixelBuffer240 = obtainPixelBufferFromResource(R.raw.libyuv_test_240_320);

                    JNIPixelFormatBean jniPixelFormatBean240 = new JNIPixelFormatBean();
                    jniPixelFormatBean240.mSrcPixelByteArray = pixelBuffer240.mSrcPixelByteArray;
                    jniPixelFormatBean240.mDestPixelByteArray = new byte[jniPixelFormatBean240.mSrcPixelByteArray.length];
                    jniPixelFormatBean240.mWidth = pixelBuffer240.mWidth;
                    jniPixelFormatBean240.mHeight = pixelBuffer240.mHeight;
                    jniPixelFormatBean240.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_I420;
                    libYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean240);

                    long currentTimeMillis = System.currentTimeMillis();
                    JNIPixelFormatBean jniPixelFormatBean2 = new JNIPixelFormatBean();
                    jniPixelFormatBean2.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_ABGR;
                    jniPixelFormatBean2.mSrcPixelByteArray = pixelBuffer240.mSrcPixelByteArray;
                    jniPixelFormatBean2.mDestPixelByteArray = new byte[jniPixelFormatBean2.mSrcPixelByteArray.length];
                    jniPixelFormatBean2.mWidth = pixelBuffer240.mWidth;
                    jniPixelFormatBean2.mHeight = pixelBuffer240.mHeight;

                    JNIPixelOptionBean jniPixelOptionBean = new JNIPixelOptionBean();
                    jniPixelOptionBean.mIsMirrored = mIsMirror;
                    mIsMirror = !mIsMirror;
                    int ret = libYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean2, jniPixelOptionBean);
                    if (ret == 0) {
                        long elapsed = System.currentTimeMillis() - currentTimeMillis;
                        mTotalElapsed += elapsed;
                        mTestCount++;
                        logI("testCount: " + mTestCount + ", total elapsed: " + mTotalElapsed + ", avg elapsed: " + (mTotalElapsed / mTestCount));
                    } else {
                        logE("ret: " + ret);
                    }
                    ByteBuffer destByteBuffer = ByteBuffer.allocate(jniPixelFormatBean2.mDestPixelByteArray.length);
                    destByteBuffer.put(jniPixelFormatBean2.mDestPixelByteArray);
                    destByteBuffer.position(0);
                    Bitmap destBitmap = Bitmap.createBitmap(jniPixelFormatBean2.mWidth, jniPixelFormatBean2.mHeight, Bitmap.Config.ARGB_8888);
                    destBitmap.copyPixelsFromBuffer(destByteBuffer);
                    mViewBinding.libyuvShowImageIv.setImageBitmap(destBitmap);
                    libYuvTest.unInitialize();
                });
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private LibYuvTest mLibYuvTest;

    private void testSrcDataLenChanged() {
        if (mLibYuvTest == null) {
            mLibYuvTest = new LibYuvTest(mContext);
            mLibYuvTest.initialize();
        }

        PixelBufferBean pixelBuffer240 = obtainPixelBufferFromResource(R.raw.libyuv_test_240_320);
        PixelBufferBean pixelBuffer480 = obtainPixelBufferFromResource(R.raw.libyuv_test_480_640);

        JNIPixelFormatBean jniPixelFormatBean240 = new JNIPixelFormatBean();
        jniPixelFormatBean240.mSrcPixelByteArray = pixelBuffer240.mSrcPixelByteArray;
        jniPixelFormatBean240.mDestPixelByteArray = new byte[jniPixelFormatBean240.mSrcPixelByteArray.length];
        jniPixelFormatBean240.mWidth = pixelBuffer240.mWidth;
        jniPixelFormatBean240.mHeight = pixelBuffer240.mHeight;
        jniPixelFormatBean240.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_I420;
        mLibYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean240);

        JNIPixelFormatBean jniPixelFormatBean480 = new JNIPixelFormatBean();
        jniPixelFormatBean480.mSrcPixelByteArray = pixelBuffer480.mSrcPixelByteArray;
        jniPixelFormatBean480.mDestPixelByteArray = new byte[jniPixelFormatBean480.mSrcPixelByteArray.length];
        jniPixelFormatBean480.mWidth = pixelBuffer480.mWidth;
        jniPixelFormatBean480.mHeight = pixelBuffer480.mHeight;
        jniPixelFormatBean480.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_I420;
        mLibYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean480);

        mViewBinding.libyuvStartTest.setOnClickListener(v -> {
            long currentTimeMillis = System.currentTimeMillis();
            JNIPixelFormatBean jniPixelFormatBean2 = new JNIPixelFormatBean();
            jniPixelFormatBean2.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_ABGR;
            int ret;
            if (mIsBigImage) {
                jniPixelFormatBean2.mSrcPixelByteArray = pixelBuffer480.mSrcPixelByteArray;
                jniPixelFormatBean2.mDestPixelByteArray = new byte[jniPixelFormatBean2.mSrcPixelByteArray.length];
                jniPixelFormatBean2.mWidth = pixelBuffer480.mWidth;
                jniPixelFormatBean2.mHeight = pixelBuffer480.mHeight;
            } else {
                jniPixelFormatBean2.mSrcPixelByteArray = pixelBuffer240.mSrcPixelByteArray;
                jniPixelFormatBean2.mDestPixelByteArray = new byte[jniPixelFormatBean2.mSrcPixelByteArray.length];
                jniPixelFormatBean2.mWidth = pixelBuffer240.mWidth;
                jniPixelFormatBean2.mHeight = pixelBuffer240.mHeight;
            }
            mIsBigImage = !mIsBigImage;
            ret = mLibYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean2, null);
            if (ret == 0) {
                logI("elapsed: " + (System.currentTimeMillis() - currentTimeMillis));
            } else {
                logE("ret: " + ret);
            }

            ByteBuffer destByteBuffer = ByteBuffer.allocate(jniPixelFormatBean2.mDestPixelByteArray.length);
            destByteBuffer.put(jniPixelFormatBean2.mDestPixelByteArray);
            destByteBuffer.position(0);
            Bitmap destBitmap = Bitmap.createBitmap(jniPixelFormatBean2.mWidth, jniPixelFormatBean2.mHeight, Bitmap.Config.ARGB_8888);
            destBitmap.copyPixelsFromBuffer(destByteBuffer);
            mViewBinding.libyuvShowImageIv.setImageBitmap(destBitmap);
        });
    }

    private void testCropScale() {
        mViewBinding.libyuvCropScaleLy.setVisibility(View.VISIBLE);
        // 通过 inScaled 和 inDensity 的设置将图片以原始的尺寸加载成 bitmap，不然系统会根据设备的像素密度自动进行缩放。
        BitmapFactory.Options op = new BitmapFactory.Options();
        op.inScaled = false;
        op.inDensity = 1;
        Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), R.raw.libyuv_test_640_480, op);
        // 通过自定义控件将图片以原始大小显示出来
        mViewBinding.libyuvShowSourceImageIv.setBitmap(bitmap);
        // 初始化 libyuv 封装对象
        LibYuvTest libYuvTest = new LibYuvTest(mContext);
        libYuvTest.initialize();
        PixelBufferBean pixelBuffer640_480 = obtainPixelBufferFromResource(R.raw.libyuv_test_640_480);
        JNIPixelFormatBean jniPixelFormatBean = new JNIPixelFormatBean();
        jniPixelFormatBean.mSrcPixelFormat = LibYuvTest.PIXEL_FORMAT_ABGR;
        jniPixelFormatBean.mDestPixelFormat = LibYuvTest.PIXEL_FORMAT_ABGR;
        jniPixelFormatBean.mSrcPixelByteArray = pixelBuffer640_480.mSrcPixelByteArray;
        jniPixelFormatBean.mDestPixelByteArray = new byte[pixelBuffer640_480.mSrcPixelByteArray.length];
        jniPixelFormatBean.mWidth = pixelBuffer640_480.mWidth;
        jniPixelFormatBean.mHeight = pixelBuffer640_480.mHeight;

        int destWidth = 0;
        int destHeight = 0;
        JNIPixelOptionBean jniPixelOptionBean = new JNIPixelOptionBean();
        // 测试旋转
//        jniPixelOptionBean.mRotate = 90;
//        destWidth = jniPixelFormatBean.mWidth;
//        destHeight = jniPixelFormatBean.mHeight;

        // 测试裁剪
//        jniPixelOptionBean.mCropX = 50;
//        jniPixelOptionBean.mCropY = 50;
//        jniPixelOptionBean.mCropWidth = jniPixelFormatBean.mWidth;
//        jniPixelOptionBean.mCropHeight = jniPixelFormatBean.mHeight;
//        destWidth = jniPixelOptionBean.mCropWidth - jniPixelOptionBean.mCropX;
//        destHeight = jniPixelOptionBean.mCropHeight - jniPixelOptionBean.mCropY;

        // 测试缩放
//        jniPixelOptionBean.mScaleWidth = 320;
//        jniPixelOptionBean.mScaleHeight = 240;
//        destWidth = jniPixelOptionBean.mScaleWidth;
//        destHeight = jniPixelOptionBean.mScaleHeight;

        // 所有参数一起测试
//        int targetWidth = 240;
//        int targetHeight = 176;
//        int[] cropArgs = calcCropArgs(pixelBuffer640_480.mWidth, pixelBuffer640_480.mHeight, targetWidth, targetHeight);
//        jniPixelOptionBean.mCropX = cropArgs[0];
//        jniPixelOptionBean.mCropY = cropArgs[1];
//        jniPixelOptionBean.mCropWidth = cropArgs[2];
//        jniPixelOptionBean.mCropHeight = cropArgs[3];
//        jniPixelOptionBean.mScaleWidth = targetWidth;
//        jniPixelOptionBean.mScaleHeight = targetHeight;
//        jniPixelOptionBean.mRotate = 0;
//        jniPixelOptionBean.mIsMirrored = true;

        int ret = libYuvTest.transformPixelFormatAndAttributes(jniPixelFormatBean, jniPixelOptionBean);
        if (ret != 0) {
            logE("ret: " + ret);
        }
        ByteBuffer destByteBuffer = ByteBuffer.wrap(jniPixelFormatBean.mDestPixelByteArray);
        Bitmap destBitmap = Bitmap.createBitmap(destWidth, destHeight, Bitmap.Config.ARGB_8888);
        destBitmap.copyPixelsFromBuffer(destByteBuffer);
        mViewBinding.libyuvShowDestImageIv.setImageBitmap(destBitmap);
    }

    private int[] calcCropArgs(int width, int height, int encodeWidth, int encodeHeight) {
        int cropX = 0;
        int cropY = 0;
        int cropWidth;
        int cropHeight;
        float widthRate = (float) width / encodeWidth;
        float heightRate = (float) height / encodeHeight;
        if (widthRate >= heightRate) {
            cropWidth = (int) (encodeWidth * heightRate);
            cropHeight = height;
            cropX = (width - cropWidth) / 2;
        } else {
            cropWidth = width;
            cropHeight = (int) (encodeHeight * widthRate);
            cropY = (height - cropHeight) / 2;
        }

        int surplusCropWidth = cropWidth % 16;
        if (surplusCropWidth != 0) {
            cropWidth -= surplusCropWidth;
            cropX = (width - cropWidth) / 2;
        }

        int surplusCropHeight = cropHeight % 16;
        if (surplusCropHeight != 0) {
            cropHeight -= surplusCropHeight;
            cropY = (height - cropHeight) / 2;
        }
        return new int[]{cropX, cropY, cropWidth, cropHeight};
    }

    private PixelBufferBean obtainPixelBufferFromResource(int resId) {
        BitmapFactory.Options op = new BitmapFactory.Options();
        op.inScaled = false;
        op.inDensity = 1;
        Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), resId, op);
        ByteBuffer byteBuffer = ByteBuffer.allocate(bitmap.getByteCount());
        bitmap.copyPixelsToBuffer(byteBuffer);
        byte[] srcPixelByteArray = new byte[bitmap.getByteCount()];
        System.arraycopy(byteBuffer.array(), byteBuffer.arrayOffset(), srcPixelByteArray, 0, bitmap.getByteCount());
        PixelBufferBean pixelBufferBean = new PixelBufferBean();
        pixelBufferBean.mSrcPixelByteArray = srcPixelByteArray;
        pixelBufferBean.mWidth = bitmap.getWidth();
        pixelBufferBean.mHeight = bitmap.getHeight();
        bitmap.recycle();
        return pixelBufferBean;
    }

    private void logI(String logMsg) {
        Log.i(TAG, logMsg);
    }

    private void logE(String logMsg) {
        Log.e(TAG, logMsg);
    }

    private static class PixelBufferBean {

        public byte[] mSrcPixelByteArray;
        public int mWidth;
        public int mHeight;

    }
}
