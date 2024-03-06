#include "NativeOAuth.h"
#include "MobileNativeCodeBlueprint.h"

namespace NativeOAuth {
	void RequestAuthCode(const FString& providerUrl)
	{
		UE_LOG(LogTemp, Warning, TEXT("providerURL: "));
#if PLATFORM_IOS
		UMobileNativeCodeBlueprint::RequestAuthCode(providerUrl);
#endif
	}
}