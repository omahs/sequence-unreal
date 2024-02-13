#if PLATFORM_ANDROID
#include <Android/AndroidJNI.h>
#include "CoreMinimal.h"

// declared in AndroidNativeBridge.java: public native void nativeHandleDeepLink(String deeplink);
JNI_METHOD void Java_com_Plugins_SequencePlugin_AndroidNativeBridge_nativeHandleDeepLink(JNIEnv* jenv, jobject thiz, jstring deeplink)
{
    const char *javaDeepLink = jenv->GetStringUTFChars(deeplink, 0);
    FString UEDeepLink = FString(UTF8_TO_TCHAR(javaDeepLink));

    UE_LOG(LogTemp, Display, TEXT("Android deep link: %s"), *UEDeepLink);
}
#endif // PLATFORM_ANDROID