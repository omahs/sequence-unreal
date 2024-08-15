// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GetChainIDArgs.generated.h"

USTRUCT(BlueprintType)
struct SEQUENCEPLUGIN_API FGetChainIDArgs
{
    GENERATED_USTRUCT_BODY()
public:
    //this guy is a nothing burger?

    bool customGetter = false;
    FString GetArgs() { return ""; }//no custom getter needed
};