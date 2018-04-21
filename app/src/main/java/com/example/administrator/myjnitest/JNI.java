package com.example.administrator.myjnitest;

import android.util.Log;

public class JNI {

    public int addnumber(int a, int b){
        Log.e("a+b = ",""+(a+b));
        return a+b;
    }
    //C语言运算加法
    public native int add(int a, int b);
    public native String sayHello(String str);
    //c改变int数组并返回
    public native int[] increaseArratEls(int[] intArray);
    public native int checkPwd(String str);
    public native void callbackAdd();
}
