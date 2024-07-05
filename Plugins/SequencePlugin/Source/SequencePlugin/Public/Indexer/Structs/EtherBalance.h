// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "EtherBalance.generated.h"

USTRUCT(BlueprintType)
struct FEtherBalance
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        FString accountAddress = "";
    UPROPERTY(BlueprintReadWrite)
        int64 balanceWei = -1;
};