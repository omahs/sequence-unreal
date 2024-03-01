#include "NativeOAuth.h"
#if PLATFORM_ANDROID
#include "Native/Android/AndroidOAuth.h"
#endif // PLATFORM_ANDROID

namespace NativeOAuth {
    void RequestAuth(const FString& providerUrl)
    {
        #if PLATFORM_ANDROID
        AndroidOAuth::AndroidThunkCpp_RequestAuth(providerUrl);
        #endif // PLATFORM_ANDROID
    }
}