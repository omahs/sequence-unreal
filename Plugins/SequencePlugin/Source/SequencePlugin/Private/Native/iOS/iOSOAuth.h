#pragma once


#if PLATFORM_IOS
//namespace iOSOAuth {

void iOS_RequestAuthCode(const FString& providerUrl, const FString& redirectScheme);

//}
#endif // PLATFORM_iOS
