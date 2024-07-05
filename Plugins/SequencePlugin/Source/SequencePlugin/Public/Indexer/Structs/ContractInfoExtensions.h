// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "ContractInfoExtensions.generated.h"

USTRUCT(BlueprintType)
struct FContractInfoExtensions
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        FString link = "";
    UPROPERTY(BlueprintReadWrite)
        FString description = "";
    UPROPERTY(BlueprintReadWrite)
        FString ogImage = "";
    UPROPERTY(BlueprintReadWrite)
        int32 originChainId = -1;//might be int64?
    UPROPERTY(BlueprintReadWrite)
        FString originAddress = "";
    UPROPERTY(BlueprintReadWrite)
        bool blacklist = false;
    UPROPERTY(BlueprintReadWrite)
        bool verified = false;
    UPROPERTY(BlueprintReadWrite)
        FString verifiedBy = "";

    /*
    * Gets the json object formed by this struct
    */
    TSharedPtr<FJsonObject> GetJson()
    {
        TSharedPtr<FJsonObject> ret = MakeShareable<FJsonObject>(new FJsonObject);
        ret.Get()->SetStringField("link", link);
        ret.Get()->SetStringField("description", description);
        ret.Get()->SetStringField("ogImage", ogImage);
        ret.Get()->SetNumberField("originChainId", originChainId);
        ret.Get()->SetStringField("originAddress", originAddress);
        ret.Get()->SetBoolField("blacklist", blacklist);
        ret.Get()->SetBoolField("verified",verified);
        ret.Get()->SetStringField("verifiedBy",verifiedBy);
        return ret;
    };
};