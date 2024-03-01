#include "Native/Android/AndroidOAuth.h"

#if PLATFORM_ANDROID
namespace AndroidOAuth {
    void AndroidThunkCpp_RequestAuthCode(const FString& providerUrl) 
    {
        if (JNIEnv* jenv{FAndroidApplication::GetJavaEnv()})   
        {
            jclass gameActivityClass{FAndroidApplication::FindJavaClass("com/epicgames/unreal/GameActivity")};
            jmethodID methodId{FJavaWrapper::FindStaticMethod(
                jenv,
                gameActivityClass, 
                "AndroidThunkJava_SequenceRequestAuthCode", 
                "(Ljava/lang/String;)V", 
                false
            )};

            jenv->CallStaticVoidMethod(
                gameActivityClass, 
                methodId, 
                AndroidOAuth::ConvertToJavaString(jenv, providerUrl)
            );

            jenv->DeleteLocalRef(gameActivityClass);
        }
    }

    jstring ConvertToJavaString(JNIEnv* jenv, const FString& string) 
    {
        const jstring localString = jenv->NewStringUTF(TCHAR_TO_UTF8(*string));
        const jstring globalString{
            static_cast<jstring>(jenv->NewGlobalRef(localString))
        };
        jenv->DeleteLocalRef(localString);
        return globalString;
    }
}

JNI_METHOD void Java_com_epicgames_unreal_GameActivity_nativeSequenceHandleDeepLink(JNIEnv* jenv, jobject thiz, jstring jdeeplinkUrl)
{
    const char* deeplinkUrlChars = jenv->GetStringUTFChars(jdeeplinkUrl, 0);

    FString deeplinkUrl;
    deeplinkUrl = FString(UTF8_TO_TCHAR(deeplinkUrlChars));

    jenv->ReleaseStringUTFChars(jdeeplinkUrl, deeplinkUrlChars);

    UE_LOG(LogTemp, Warning, TEXT("NativeOAuth: deep link url from java: %s"), *deeplinkUrl);
}
#endif // PLATFORM_ANDROID