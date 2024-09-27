#pragma once

#include "CoreMinimal.h"
#include "SeqFeeBreakdown.h"
#include "Marketplace/Marketplace_Enums.h"
#include "Util/SequenceSupport.h"
#include "SeqOrder.generated.h"

USTRUCT(BlueprintType)
struct SEQUENCEPLUGIN_API FSeqOrder
{
    GENERATED_USTRUCT_BODY()

public:

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString OrderId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    TEnumAsByte<EMarketplaceKind> Marketplace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    TEnumAsByte<EOrderSide> Side;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    TEnumAsByte<EOrderStatus> Status;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    int64 ChainId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString CollectionContractAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString TokenId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString CreatedBy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString PriceAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString PriceAmountFormatted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString PriceAmountNet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString PriceAmountNetFormatted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString PriceCurrencyAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    int64 PriceDecimals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    double PriceUSD;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityInitial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityInitialFormatted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityRemaining;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityRemainingFormatted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityAvailable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString QuantityAvailableFormatted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    int64 QuantityDecimals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    int64 FeeBps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    TArray<FSeqFeeBreakdown> FeeBreakdown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString ValidFrom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString ValidUntil;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString OrderCreatedAt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString OrderUpdatedAt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString CreatedAt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString UpdatedAt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
    FString DeletedAt;

    bool customConstructor = true;

    TSharedPtr<FJsonObject> GetJson()
    {
        TSharedPtr<FJsonObject> ret = MakeShareable(new FJsonObject);
        ret->SetStringField("orderId", OrderId);
        ret->SetStringField("marketplace", UEnum::GetValueAsString(Marketplace.GetValue()));
        ret->SetStringField("side", UEnum::GetValueAsString(Side.GetValue()));
        ret->SetStringField("status", UEnum::GetValueAsString(Status.GetValue()));
        ret->SetNumberField("chainId", ChainId);
        ret->SetStringField("collectionContractAddress", CollectionContractAddress);
        ret->SetStringField("tokenId", TokenId);
        ret->SetStringField("createdBy", CreatedBy);
        ret->SetStringField("priceAmount", PriceAmount);
        ret->SetStringField("priceAmountFormatted", PriceAmountFormatted);
        ret->SetStringField("priceAmountNet", PriceAmountNet);
        ret->SetStringField("priceAmountNetFormatted", PriceAmountNetFormatted);
        ret->SetStringField("priceCurrencyAddress", PriceCurrencyAddress);
        ret->SetNumberField("priceDecimals", PriceDecimals);
        ret->SetNumberField("priceUSD", PriceUSD);
        ret->SetStringField("quantityInitial", QuantityInitial);
        ret->SetStringField("quantityInitialFormatted", QuantityInitialFormatted);
        ret->SetStringField("quantityRemaining", QuantityRemaining);
        ret->SetStringField("quantityRemainingFormatted", QuantityRemainingFormatted);
        ret->SetStringField("quantityAvailable", QuantityAvailable);
        ret->SetStringField("quantityAvailableFormatted", QuantityAvailableFormatted);
        ret->SetNumberField("quantityDecimals", QuantityDecimals);
        ret->SetNumberField("feeBps", FeeBps);

        // Serialize FeeBreakdown array
        TArray<TSharedPtr<FJsonValue>> feeBreakdownArray;
        for (FSeqFeeBreakdown& fee : FeeBreakdown)
        {
            feeBreakdownArray.Add(MakeShareable(new FJsonValueObject(fee.GetJson())));
        }
        ret->SetArrayField("feeBreakdown", feeBreakdownArray);

        ret->SetStringField("validFrom", ValidFrom);
        ret->SetStringField("validUntil", ValidUntil);
        ret->SetStringField("orderCreatedAt", OrderCreatedAt);
        ret->SetStringField("orderUpdatedAt", OrderUpdatedAt);
        ret->SetStringField("createdAt", CreatedAt);
        ret->SetStringField("updatedAt", UpdatedAt);
        ret->SetStringField("deletedAt", DeletedAt);
        return ret;
    }

    void Setup(FJsonObject& json_in)
    {
        OrderId = json_in.GetStringField("orderId");

        if (!json_in.TryGetField(TEXT("marketplace")))
            Marketplace = EMarketplaceKind(json_in.GetIntegerField(TEXT("marketplace")));

        if (!json_in.TryGetField(TEXT("side")))
            Side = EOrderSide(json_in.GetIntegerField(TEXT("side")));

        if (!json_in.TryGetField(TEXT("status")))
            Status = EOrderStatus(json_in.GetIntegerField(TEXT("Status")));

        ChainId = json_in.GetNumberField("chainId");
        CollectionContractAddress = json_in.GetStringField("collectionContractAddress");
        TokenId = json_in.GetStringField("tokenId");
        CreatedBy = json_in.GetStringField("createdBy");
        PriceAmount = json_in.GetStringField("priceAmount");
        PriceAmountFormatted = json_in.GetStringField("priceAmountFormatted");
        PriceAmountNet = json_in.GetStringField("priceAmountNet");
        PriceAmountNetFormatted = json_in.GetStringField("priceAmountNetFormatted");
        PriceCurrencyAddress = json_in.GetStringField("priceCurrencyAddress");
        PriceDecimals = json_in.GetNumberField("priceDecimals");
        PriceUSD = json_in.GetNumberField("priceUSD");
        QuantityInitial = json_in.GetStringField("quantityInitial");
        QuantityInitialFormatted = json_in.GetStringField("quantityInitialFormatted");
        QuantityRemaining = json_in.GetStringField("quantityRemaining");
        QuantityRemainingFormatted = json_in.GetStringField("quantityRemainingFormatted");
        QuantityAvailable = json_in.GetStringField("quantityAvailable");
        QuantityAvailableFormatted = json_in.GetStringField("quantityAvailableFormatted");
        QuantityDecimals = json_in.GetNumberField("quantityDecimals");
        FeeBps = json_in.GetNumberField("feeBps");

        if (json_in.HasField(TEXT("feeBreakdown"))) 
        {
            const TArray<TSharedPtr<FJsonValue>>& feeBreakdownArray = json_in.GetArrayField(TEXT("feeBreakdown")); 
            FeeBreakdown.Empty();
            for (int32 i = 0; i < feeBreakdownArray.Num(); ++i) 
            {
                TSharedPtr<FJsonValue> feeValue = feeBreakdownArray[i];
                if (feeValue->Type == EJson::Object)
                {
                    FSeqFeeBreakdown fee;
                    TSharedPtr<FJsonObject> feeJsonObject = USequenceSupport::JsonStringToObject(feeValue->AsString()); 
                    fee.Setup(*feeJsonObject); 
                    FeeBreakdown.Add(fee); 
                }
            }
        }

        ValidFrom = json_in.GetStringField("validFrom");
        ValidUntil = json_in.GetStringField("validUntil");
        OrderCreatedAt = json_in.GetStringField("orderCreatedAt");
        OrderUpdatedAt = json_in.GetStringField("orderUpdatedAt");
        CreatedAt = json_in.GetStringField("createdAt");
        UpdatedAt = json_in.GetStringField("updatedAt");
        DeletedAt = json_in.GetStringField("deletedAt");
    }
};