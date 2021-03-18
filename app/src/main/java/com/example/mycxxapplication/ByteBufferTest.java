package com.example.mycxxapplication;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;

import java.nio.ByteBuffer;

public class ByteBufferTest {

    private static final String IMAGE_PATH = "/mnt/sdcard/1.jpg";
    private static final int RENDER_COUNT = 500;

    private ByteBuffer mBuffer;
    private boolean mStarted;
    private byte[] mSrcArray;
    private int mWidth, mHeight;
    private SurfaceView[] mSurfaces;
    private Context mContext;

    public ByteBufferTest(Context context) {
        mContext = context;
    }

    public void start(SurfaceView[] surfaces) {
        if (mStarted) {
            return;
        }
        mStarted = true;
        mSurfaces = surfaces;
        mSrcArray = getByteArray();
        mBuffer = ByteBuffer.allocateDirect(mSrcArray.length);
        setByteBuffer(mBuffer);
        new Thread(new Runnable() {
            @Override
            public void run() {
                long l = System.currentTimeMillis();
                int renderCount = RENDER_COUNT;
                while (renderCount > 0) {
                    renderCount--;
//                    Canvas canvas = mSurfaces[0].getHolder().lockCanvas();
//                    canvas.drawBitmap(mBitmap, 0,0,null);
//                    mSurfaces[0].getHolder().unlockCanvasAndPost(canvas);
                    renderBitmap2(mSrcArray, mSurfaces[0].getHolder().getSurface(), mWidth, mHeight, mSrcArray.length);
                }
                Log.d("wzgccc", " 11111 : " + (System.currentTimeMillis() - l));
            }
        }).start();
//
        new Thread(new Runnable() {
            @Override
            public void run() {
                long l = System.currentTimeMillis();
                int renderCount = RENDER_COUNT;
                while (renderCount > 0) {
                    renderCount--;
                    mBuffer.put(mSrcArray);
                    mBuffer.flip();
                    renderBitmap(mSurfaces[1].getHolder().getSurface(), mWidth, mHeight, mSrcArray.length);
                }
                Log.d("wzgccc", " 2222 : " + (System.currentTimeMillis() - l));
            }
        }).start();
    }

    private Bitmap mBitmap;
    private byte[] getByteArray() {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;
        Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.bytebuffertest, options);
        mWidth = bitmap.getWidth();
        mHeight = bitmap.getHeight();
        ByteBuffer buffer = ByteBuffer.allocate(mWidth * mHeight * 4);
        bitmap.copyPixelsToBuffer(buffer);
        buffer.flip();

//        Bitmap bitmap1 = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
//        bitmap1.copyPixelsFromBuffer(buffer);
//
//        ByteBuffer buffer1 = ByteBuffer.allocate(bitmap1.getByteCount());
//        bitmap1.copyPixelsToBuffer(buffer1);
//        buffer1.flip();
        mBitmap = bitmap;
        return buffer.array();
    }

    private native void setByteBuffer(ByteBuffer buffer);

    private native void renderBitmap(Surface surface, int width, int height, int bufferLen);

    private native void renderBitmap2(byte[] array, Surface surface, int width, int height, int bufferLen);
}
