package com.example.administrator.myjnitest;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private Button button_data1;
    private Button button_data2;
    private Button button_data3;
    private Button button_data4;
    private Button button_data5;
    private Button button_data6;
    private JNI  jni;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jni = new JNI();
        button_data1 = findViewById(R.id.button_data1);
        button_data2 = findViewById(R.id.button_data2);
        button_data3 = findViewById(R.id.button_data3);
        button_data4 = findViewById(R.id.button_data4);
        button_data5 = findViewById(R.id.button_data5);
        button_data6 = findViewById(R.id.button_data6);


        button_data1.setOnClickListener(this);
        button_data2.setOnClickListener(this);
        button_data3.setOnClickListener(this);
        button_data4.setOnClickListener(this);
        button_data5.setOnClickListener(this);
        button_data6.setOnClickListener(this);

    }

    /**
     * A native method that is implement
     * ed by the 'native-lib' native library,
     * which is packaged with this application.
     */


    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.button_data1:
                Log.i("-----",""+stringFromJNI());
//                Toast.makeText(this, ""+getint(35, 48), Toast.LENGTH_SHORT).show();
                break;
            case R.id.button_data2:
                Toast.makeText(this, ""+getString("tt"), Toast.LENGTH_SHORT).show();
                break;
            case R.id.button_data3:
                String[] arr2 = getArray();
                int[] arr = new int[]{1,2,3};
                int m = getsum(arr);
                for (String a:arr2){
                    Log.i("hongbiao-------",""+m);
                }
                break;
            case R.id.button_data4:
                Student[]  students = (Student[]) getArr();
                for (int i=0;i<students.length;i++){
                    Log.i("student----",students[i].getName());
                }
                break;
            case R.id.button_data5:
                callMethod();
                break;
            case  R.id.button_data6:
                Toast.makeText(this, ""+jni.sayHello("hello java "), Toast.LENGTH_SHORT).show();
                Toast.makeText(this, "jni中求和为："+jni.add(3,8), Toast.LENGTH_SHORT).show();
                break;


        }
    }
    public static void  JNIcallJava(){
        Log.i("test class","when you have seen this you are sucess");
    }

    
    public native String stringFromJNI();
    public native int getint(int a,int b);
    public native String getString(String str);
    public native String[] getArray();
    public native int getsum(int[] arr);

    public native Object[] getArr();
    public native  void callMethod();

}
