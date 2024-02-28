#include "NativeOAuth.h"
#include "iOS/iOSOAuth.h"


	void testingFunction()
	{
		UE_LOG(LogTemp,Display,TEXT("Print some stuff"));
	}
	
	void RequestAuthCode(const FString& providerUrl, const FString& redirectScheme)
	{
#if PLATFORM_IOS
		iOS_RequestAuthCode(providerUrl, redirectScheme);
#endif 
	}