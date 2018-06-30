package com.jnidemo;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;

import static android.R.attr.bitmap;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native");
    }
    ImageView img;
    Button btn;
    Bitmap mBitmap;
    private final String TAG = "zzk";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        initView();

    }

    private void initView() {
        img = (ImageView) findViewById(R.id.imageView);
        btn = (Button)findViewById(R.id.button);
        try {
            InputStream in = getResources().getAssets().open("lady.jpg");
            int lenght = in.available();
            byte[] buffer = new byte[lenght];
            in.read(buffer);
            //转换为BitMap
            BitmapFactory.Options opts = new BitmapFactory.Options();
            mBitmap = BitmapFactory.decodeByteArray(buffer,0,buffer.length,opts);
            img.setImageBitmap(mBitmap);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void click(View v){
        Log.d(TAG,"click");
        int width = mBitmap.getWidth();
        int height = mBitmap.getHeight();
        int size = mBitmap.getByteCount();
        byte[] array = new byte[size];
        ByteBuffer buf = ByteBuffer.wrap(array);
        Log.d(TAG,"width:"+width+"height:"+height+"size:"+size+"RowBytes:"+mBitmap.getRowBytes());
        //从bitmap中取像素值到buffer中，像素值类型为ARGB
        mBitmap.copyPixelsToBuffer(buf);

        //将Bitmap转换的字节数组，传递给jni，进行处理（当前为灰度化）
        ProcessResult processResult = processByteArray(array, width, height);
        String strResult = null;
        try {
            strResult = new String(processResult.strResult,"gbk");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        Log.d(TAG,"after processByteBuf:"+strResult+
                " pos("+processResult.x+","+processResult.y+"    "+processResult.width+","+processResult.height+")");
        Toast.makeText(MainActivity.this, strResult, Toast.LENGTH_LONG).show();

        //jni处理后的数据，回放到Bitmap
        buf.rewind();//将buffer的下一读写位置置为0
        mBitmap.copyPixelsFromBuffer(buf);
        Log.d(TAG,"after copyPixelsFromBuffer");

        //显示图片
        img.setImageBitmap(mBitmap);
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromC();
    public static native ProcessResult processByteArray(byte[] data,int w, int h);
    public static native void blurBitmap(Bitmap bitmap, int r);
}
