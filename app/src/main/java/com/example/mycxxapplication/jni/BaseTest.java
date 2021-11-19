package com.example.mycxxapplication.jni;

import android.content.Context;

import java.nio.ByteBuffer;

public abstract class BaseTest {

    protected Context mContext;

    public BaseTest(Context context) {
        this.mContext = context;
    }

    public abstract void startTest();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        BaseTest baseTest = (BaseTest) o;

        return mContext != null ? mContext.equals(baseTest.mContext) : baseTest.mContext == null;
    }

    @Override
    public int hashCode() {
        return mContext != null ? mContext.hashCode() : 0;
    }
}
