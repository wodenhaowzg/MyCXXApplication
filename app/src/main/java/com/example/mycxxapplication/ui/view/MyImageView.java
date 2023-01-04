package com.example.mycxxapplication.ui.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.Nullable;

public class MyImageView extends View {

    private Bitmap mBitmap;
    private Paint mPaint;
    private Matrix matrix;

    public MyImageView(Context context) {
        super(context, null);
    }

    public MyImageView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        mPaint = new Paint();
        matrix = new Matrix();
        matrix.reset();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if (mBitmap != null) {
            canvas.drawColor(Color.BLACK);
            canvas.drawBitmap(mBitmap, matrix, mPaint);
        }
    }

    public void setBitmap(Bitmap bitmap) {
        mBitmap = bitmap;
        postInvalidate();
    }
}
