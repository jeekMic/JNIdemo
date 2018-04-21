//
// Created by Administrator on 2018/4/20.
//

#include <jni.h>
#include <string.h>
#include <malloc.h>
#include <android/log.h>
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) // 定义LOGF类型
char* _JString2CStr(JNIEnv *env, jstring jstr){
    char* rtn = NULL;
    //找到java中的String这个类
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    //获取指定的编码
    jstring strencode = (*env)->NewStringUTF(env,"GB2312");
    /*
     *获得java类中getBytes这个方法,第二个参数为类, 第三个参数为诶方法名, 第四个参数为括号内表示需要的参数,[B表示返回一个byte的数组
     * mid可以理解为方法的引用一样,只要调用即可
     */
    jmethodID mid = (*env)->GetMethodID(env,clsstring,"getBytes", "(Ljava/lang/String;)[B");
    /**
     * 这里就是调用这个方法了
     * 参数1：环境
     * 参数2：从java出拿到的字符串
     * 参数3：需要调用的方法
     * 参数3,编码格式
     * 返回: 返回jbyteArray数组
     */
    jbyteArray  barr = (jbyteArray)(*env)->CallObjectMethod(env,jstr,mid,strencode);
    //获取jbyteArrays数组的长度
    jsize alen = (*env)->GetArrayLength(env,barr);
    //定义一个byte指针指向上面的这个jbyteArray数组
    jbyte *ba = (*env)->GetByteArrayElements(env, barr,JNI_FALSE);

    if(alen>0){
        //数组一般会以一个\0结束，所以需要多加一位
        rtn = (char*)malloc(alen+1);
        //c中memcoy函数的意思是从ba中赋值alen到rtn中去
        memcpy(rtn,ba,alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env,barr,ba,0);
    return rtn;
}

jint  Java_com_example_administrator_myjnitest_JNI_add(JNIEnv *env,jobject instance, jint a, jint b){
    jint  m = a+b;
    return m;
}

JNIEXPORT jstring JNICALL Java_com_example_administrator_myjnitest_JNI_sayHello(JNIEnv *env,jobject job, jstring jstr){

    char *fromjava = _JString2CStr(env,jstr) ;
    char *fromC = "add i am from c";
    strcat(fromjava,fromC);
    return (*env)->NewStringUTF(env,fromjava);
}
/**
 * 给每个元素加上10
 * @param env
 * @param job
 * @param jarray
 * @return
 */
JNIEXPORT jintArray JNICALL Java_com_example_administrator_myjnitest_JNI_increaseArratEls(JNIEnv *env, jobject job, jintArray jarray){
    //1,得到数组长度
    //size
    jint size = (*env)->GetArrayLength(env,jarray);
    int a;
    //2，得到数组
    jint  *intArray = (*env)->GetIntArrayElements(env,jarray,JNI_FALSE);
    //3，遍历数组,给每个数组加上10
    int i;
    int k = 10;
    for(i=0;i<size;i++){
        *(intArray+i) += k;
        a = *(intArray+i);
    }

    //返回结果
    return jarray;

}
JNIEXPORT jint JNICALL Java_com_example_administrator_myjnitest_JNI_checkPwd(JNIEnv *env, jobject jobj, jstring jstr){
    char *origin = "123456";
    char *fromUser = _JString2CStr(env,jstr);
    //函数比较字符串是否相等
    int code = strcmp(origin,fromUser);
    if(code==0){
        return 200;
    } else{
        return 400;
    }
}
//c调用java代码
JNIEXPORT void JNICALL Java_com_example_administrator_myjnitest_JNI_callbackAdd(JNIEnv *env, jobject obj){
    /**
     *  1，获得java字节码也就是jclass 一般是都是 FindClass
     *   jclass      (*FindClass)(JNIEnv*, const char*);
     */

    jclass jclassz = (*env)->FindClass(env,"com/example/administrator/myjnitest/JNI");
    /*
      * 2，获得方法 也就是jmethodID
      *  jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
     */
     jmethodID jmethodIDs = (*env)->GetMethodID(env,jclassz,"addnumber","(II)I");

     /*
      * 3实例化类
      */
     jobject jobject = (*env)->AllocObject(env,jclassz);
    /**
     * 调用方法
     * jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
     */
    int m = 10;

    (*env)->CallIntMethod(env, jobject,jmethodIDs, 8,9);
 }