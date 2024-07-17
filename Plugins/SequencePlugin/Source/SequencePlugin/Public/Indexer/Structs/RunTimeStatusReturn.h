// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "RuntimeStatus.h"
#include "Dom/JsonObject.h"
#include "RuntimeStatusReturn.generated.h"

USTRUCT(BlueprintType)
struct FRuntimeStatusReturn
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY()
        FRuntimeStatus status;
    bool customConstructor = false;//used to tell buildresponse whether or not to use a custom constructor OR the unreal one!
    void construct(FJsonObject json_in) {};//dummy construct for templating
    void Setup(FJsonObject json_in) {};//dummy method to allow for templating in build response!
};