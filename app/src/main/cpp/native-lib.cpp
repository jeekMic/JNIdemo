#include <jni.h>
#include <string>
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
JNIEXPORT void JNICALL
Java_com_example_administrator_myjnitest_MainActivity_set(JNIEnv *env, jclass type, jint i) {

    // TODO

}