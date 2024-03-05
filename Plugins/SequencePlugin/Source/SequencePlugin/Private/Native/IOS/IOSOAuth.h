#pragma once

#if PLATFORM_IOS
namespace IOSOAuth {
	void RequestAuthCode(const FString& providerUrl);
}
#endif