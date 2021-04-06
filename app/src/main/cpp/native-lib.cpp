#include <jni.h>
#include <string>
#include <cpr/cpr.h>
#include <android/log.h>

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *pjvm, void *reserved) {

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jstring JNICALL
Java_test_jni_cpr_MainActivity_request(
        JNIEnv* env,
        jobject /* this */
        , jstring jUrl
        , jstring jCaPath
        ) {
    const char *cUrl = env->GetStringUTFChars(jUrl, NULL);
    std::string runtimeDir(cUrl);
    env->ReleaseStringUTFChars(jUrl, cUrl);

    const char *caPath = env->GetStringUTFChars(jCaPath, NULL);
    std::string caFilePath(caPath);
    env->ReleaseStringUTFChars(jCaPath, caPath);

    cpr::Session session{};
    session.SetUrl(cpr::Url{cUrl});

    #ifdef ANDROID
    auto sslOpts  = cpr::Ssl(cpr::ssl::CaPath{caFilePath.c_str()});
    session.SetOption(sslOpts);
    #endif // ANDROID

    cpr::Response response = session.Get();

    __android_log_print(ANDROID_LOG_INFO, "TEST", "status = %ld", response.status_code);
    __android_log_print(ANDROID_LOG_ERROR, "ERROR", "error = %s", response.error.message.c_str());
    __android_log_print(ANDROID_LOG_INFO, "TEST", "response = %s", response.text.c_str());

    return env->NewStringUTF(response.text.c_str());
}
