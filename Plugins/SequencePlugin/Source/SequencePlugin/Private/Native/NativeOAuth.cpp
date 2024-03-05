#include "NativeOAuth.h"
#include "Native/IOS/IOSOAuth.h"

namespace NativeOAuth {
	void RequestAuthCode(const FString& providerUrl)
	{
		UE_LOG(LogTemp, Warning, TEXT("providerURL: "));
		#if PLATFORM_IOS
		IOSOAuth::RequestAuthCode(providerUrl);
		#endif
	}
}
