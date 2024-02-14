#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"

// declared in AndroidNativeBridge.java: public native void nativeHandleDeepLink(String deeplink);
JNI_METHOD void Java_com_epicgames_unreal_GameActivity_nativeHandleDeepLink(JNIEnv* jenv, jobject thiz, jstring jdeeplink) 
{
    const char *deeplinkChars = jenv->GetStringUTFChars(deeplink, 0);
    FString deeplink = FString(UTF8_TO_TCHAR(deeplinkChars));
    
    jenv->ReleaseStringUTFChars(jdeeplink, deeplinkChars);

    UE_LOG(LogTemp, Display, TEXT("Android deep link: %s"), *deeplink);
}
#endif // PLATFORM_ANDROID