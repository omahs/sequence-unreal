#include "NativeOAuth.h"
#if PLATFORM_IOS
#include "Native/iOS/iOSOAuth.h"
#endif // PLATFORM_IOS

namespace NativeOAuth {
	void RequestAuthCode(const FString& providerUrl, const FString& redirectScheme)
	{
#if PLATFORM_IOS
		iOSOAuth::iOS_RequestAuthCode(providerUrl, redirectScheme);
#endif // PLATFORM_IOS
	}
}