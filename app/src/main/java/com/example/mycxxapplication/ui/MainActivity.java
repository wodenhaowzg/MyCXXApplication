package com.example.mycxxapplication.ui;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Point;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.mycxxapplication.R;
import com.example.mycxxapplication.jni.CollectionTest;
import com.example.mycxxapplication.jni.PointerTest;
import com.example.mycxxapplication.jni.StringTest;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d("TimeUtils", "java currentTimeMillis : " + System.currentTimeMillis());
        Log.d("TimeUtils", "java nanoTime : " + System.nanoTime());
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

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

//        MemoryTest memoryTest = new MemoryTest(this);
//        memoryTest.startTest();

//        BaseTypeTest memoryTest = new BaseTypeTest(this);
//        memoryTest.startTest();

//        CollectionTe.starst collectionTest = new CollectionTest(this);
//        collectionTesttTest();

//        StringTest stringTest = new StringTest(this);
//        stringTest.startTest();

//        PointerTest pointerTest = new PointerTest(this);
//        pointerTest.startTest();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void testBase();
}
