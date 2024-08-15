// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Indexer/Indexer_Enums.h"
#include "ContractInfo.h"
#include "TokenMetaData.h"
#include "TokenBalance.generated.h"

USTRUCT(BlueprintType)
struct SEQUENCEPLUGIN_API FTokenBalance
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int32 id = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        FString contractAddress = "";
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        TEnumAsByte<EContractType> contractType = EContractType::ERC1155;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        FString accountAddress = "";
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int64 tokenID = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int64 balance = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        FString blockHash = "";
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int64 blockNumber = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int64 updateID = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        int64 chainId = -1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        FContractInfo contractInfo;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
        FTokenMetaData tokenMetaData;

    /*
    * Used to get the json object formed by this struct
    * used for testing and args
    */
    TSharedPtr<FJsonObject> GetJson()
    {
        TSharedPtr<FJsonObject> ret = MakeShareable<FJsonObject>(new FJsonObject);
        ret.Get()->SetNumberField("id", id);
        ret.Get()->SetStringField("contractAddress", contractAddress);
        ret.Get()->SetStringField("contractType", UEnum::GetValueAsString(contractType.GetValue()));
        ret.Get()->SetStringField("accountAddress", accountAddress);
        ret.Get()->SetNumberField("tokenID", tokenID);
        ret.Get()->SetNumberField("balance", balance);
        ret.Get()->SetStringField("blockHash",blockHash);
        ret.Get()->SetNumberField("blockNumber", blockNumber);
        ret.Get()->SetNumberField("updateID", updateID);
        ret.Get()->SetNumberField("chainId", chainId);
        ret.Get()->SetObjectField("contractInfo", contractInfo.GetJson());
        ret.Get()->SetObjectField("tokenMetaData", tokenMetaData.GetJson());
        return ret;
    };

    /*
    * Used for handling edge cases with unreal's parsing
    */
    void setup(FJsonObject json_in)
    {
        const TSharedPtr<FJsonObject> *item;
        if (json_in.TryGetObjectField(TEXT("tokenMetaData"), item))
        {
            tokenMetaData.setup(*item->Get());
        }
    }//setup
};