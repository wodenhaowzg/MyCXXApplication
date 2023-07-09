package com.example.mycxxapplication.ui;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.View;

import androidx.databinding.DataBindingUtil;

import com.example.mycxxapplication.R;
import com.example.mycxxapplication.databinding.ActivityMainBinding;
import com.example.mycxxapplication.jni.BaseTest;
import com.example.mycxxapplication.jni.ObjectTest;
import com.example.mycxxapplication.libyuv.LibYuvTest;

public class MainActivity extends BaseActivity {

    private static final String TAG = "MainActivity";
    private ActivityMainBinding mViewBinding;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mViewBinding = DataBindingUtil.setContentView(this, R.layout.activity_main);

        mViewBinding.mainTestLibyuv.setOnClickListener(v -> startActivity(new Intent(mContext, LibYuvTestActivity.class)));

//        findViewById(R.id.test_bytebuffer).setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                SurfaceView surfaceView1 = findViewById(R.id.test_bytebuffer_surface1);
//                SurfaceView surfaceView2 = findViewById(R.id.test_bytebuffer_surface2);
//                SurfaceView[] surfaces = new SurfaceView[]{surfaceView1, surfaceView2};
//                ByteBufferTest byteBufferTest = new ByteBufferTest(MainActivity.this);
//                byteBufferTest.start(surfaces);
//            }
//        });

        BaseTest baseTest = new BaseTest(this);
        baseTest.startTest();

//        MemoryTest memoryTest = new MemoryTest(this);
//        memoryTest.startTest();

//        BaseTypeTest memoryTest = new BaseTypeTest(this);
//        memoryTest.startTest();

//        CollectionTe.starst collectionTest = new CollectionTest(this);
//        collectionTesttTest();

//        StringTest stringTest = new StringTest();
//        stringTest.startTest();

//        PointerTest pointerTest = new PointerTest(this);
//        pointerTest.startTest();

//        ObjectTest objectTest = new ObjectTest();
//        objectTest.startTest();

//        ComponentTest componentTest = new ComponentTest();
//        componentTest.startTest();

//        JNITransDataTest jniTransDataTest = new JNITransDataTest(this);
//        jniTransDataTest.startTest();
    }
}
