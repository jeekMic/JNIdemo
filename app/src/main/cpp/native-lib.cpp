#include <jni.h>
#include <string>
#include <malloc.h>
#include <string.h>
#include <android/log.h>
#define LOG_TAG "System.out"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#include <stdio.h>


/**
 * 可以将*env理解为一种环境 就object为一种java类
 */
extern "C" JNIEXPORT jstring
JNICALL
Java_com_example_administrator_myjnitest_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    using namespace std; //命名空间
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_administrator_myjnitest_MainActivity_getint(JNIEnv *env, jobject instance, jint a, jint b) {

    // TODO
    jint m = 0;
    m = a+b;
    return m;


}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_administrator_myjnitest_MainActivity_getString(JNIEnv *env, jobject instance,
                                                                jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    if(strlen(str)>0){
        for(int i=0;i<strlen(str);i++){
            str+=1;
        }
    }
    LOGD("----",str);
    // TODO
    env->ReleaseStringUTFChars(str_, str);

    return env->NewStringUTF(str);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_administrator_myjnitest_MainActivity_getArray(JNIEnv *env, jobject instance) {

    jstring      str; //定义一个
    jobjectArray args = 0;
    jsize        len = 5;
    const char* sa[] = { "Hello,", "world!", " JNI", " is", " fun" };
    //int          i=0;
    args = env->NewObjectArray(len, (env)->FindClass("java/lang/String"), 0);
    for(int i = 0; i < len; i++)
    {
        str = (env)->NewStringUTF(sa[i]);
        (env)->SetObjectArrayElement(args, i, str);
    }
    return args;

}extern "C"
JNIEXPORT jint JNICALL
Java_com_example_administrator_myjnitest_MainActivity_getsum(JNIEnv *env, jobject instance, jintArray arr) {

    // TODO
    jint *carr;
    jint i, sum = 0;
    carr = env->GetIntArrayElements(arr, NULL);
    if (carr == NULL) {
        return 0; /* exception occurred */
    }
    for (i=0; i<10; i++)
    {
        sum += carr[i];
        LOGD("----%d",sum);
    }
    return sum;

}extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_administrator_myjnitest_MainActivity_getArr(JNIEnv *env, jobject instance) {

    // 声明一个object的数组
    jobjectArray  args = 0;

    //数组大小
    jsize len = 5;


    //获取object所属类,一般为java/lang/Object就可以了
    jclass obj = env->FindClass("java/lang/Object");
    jclass student = env->FindClass("com/example/administrator/myjnitest/Student");
    args = env->NewObjectArray(len,student,0);
    jmethodID  m_mid_stu = env->GetMethodID(student, "<init>", "()V");
    jfieldID  str_name = env->GetFieldID(student,"name","Ljava/lang/String;");
    jfieldID  str_age = env->GetFieldID(student,"age","I");
    for(int i=0;i<len;i++){
        jobject stu_1 = env->NewObject(student,m_mid_stu);
        env->SetObjectField(stu_1,str_name,env->NewStringUTF("student"));
        env->SetIntField(stu_1,str_age,10+i);
        env->SetObjectArrayElement(args,i,stu_1);
    }
    return args;
}