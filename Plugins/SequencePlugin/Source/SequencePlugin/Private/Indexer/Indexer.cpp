// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.

#include "Indexer/Indexer.h"
#include "Util/Async.h"
#include "JsonObjectConverter.h"
#include "Http.h"
#include "HttpManager.h"

UIndexer::UIndexer(){}

/*
	Combines <see cref="PATH" and name="name" to suffix on to the base address
*/
FString UIndexer::Url(const int64& ChainID,const FString& EndPoint) const
{
	FString Out_URL = HostName(ChainID);
	Out_URL.Append(this->PATH);
	
	if (EndPoint.Len() > 0)
	{
		Out_URL.Append(EndPoint);
	}
	return Out_URL;
}

/*
	Get hostname directing to specific chainID
*/
FString UIndexer::HostName(const int64 ChainID)
{
	FString Hostname = "https://";
	Hostname.Append(USequenceSupport::GetNetworkName(ChainID));
	Hostname.Append("-indexer.sequence.app");
	return Hostname;
}

/*
	Here we construct a post request and parse out a response if valid.
*/
void UIndexer::HTTPPost(const int64& ChainID,const FString& Endpoint,const FString& Args, const TSuccessCallback<FString>& OnSuccess, const FFailureCallback& OnFailure) const
{
	const TSharedRef<IHttpRequest> HTTP_Post_Req = FHttpModule::Get().CreateRequest();
	
	HTTP_Post_Req->SetVerb("POST");
	HTTP_Post_Req->SetHeader("Content-Type", "application/json");//2 differing headers for the request
	HTTP_Post_Req->SetHeader("Accept", "application/json");
	HTTP_Post_Req->SetTimeout(30);
	HTTP_Post_Req->SetURL(this->Url(ChainID, Endpoint));
	HTTP_Post_Req->SetContentAsString(Args);
	HTTP_Post_Req->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](const FHttpRequestPtr& Request, FHttpResponsePtr Response, const bool bWasSuccessful)
	{ 
		if(bWasSuccessful)
		{
			const FString Content = Request->GetResponse()->GetContentAsString();
			OnSuccess(Content);
		}
		else
		{
			if(Request.IsValid() && Request->GetResponse().IsValid())
			{
				OnFailure(FSequenceError(RequestFail, "Request failed: " + Request->GetResponse()->GetContentAsString()));
			}
			else
			{
				OnFailure(FSequenceError(RequestFail, "Request failed: Invalid Request Pointer"));
			}
			
		}
	});
	HTTP_Post_Req->ProcessRequest();
}

/*
	Here we take in a struct and convert it straight into a json object String
	@Param (T) Struct_in the struct we are converting to a json object string
	@Return the JSON Object String
*/
template < typename T> FString UIndexer::BuildArgs(T StructIn)
{
	FString Result = "[FAILED TO PARSE]";
	if (StructIn.customGetter)
	{
		Result = StructIn.GetArgs();
	}
	else
	{
		if (!FJsonObjectConverter::UStructToJsonObjectString<T>(StructIn, Result))
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to convert specified UStruct to a json object\n"));
		}
	}
	return Result;
}

//generic
template<typename T> T UIndexer::BuildResponse(const FString Text)
{
	//Take the FString and convert it to a JSON object first!
	TSharedPtr<FJsonObject> JSON_Step;
	//Then take the json object we make and convert it to a USTRUCT of type T then we return that!
	T Ret_Struct;

	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), JSON_Step))
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to convert String: %s to Json object"), *Text);
		return T();
	}
	//this next line with throw an exception in null is used as an entry in json attributes! we need to remove null entries
	if (Ret_Struct.customConstructor) 
	{//use the custom constructor!
		Ret_Struct.construct(*JSON_Step.Get());
	}
	else
	{//use unreal parsing!
		if (!FJsonObjectConverter::JsonObjectToUStruct<T>(JSON_Step.ToSharedRef(), &Ret_Struct))
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to convert Json Object: %s to USTRUCT of type T"), *Text);
			return T();
		}
	}
	Ret_Struct.Setup(*JSON_Step.Get());//now for the edge cases we will manually inject the data where it needs to be!
	return Ret_Struct;
}

void UIndexer::Ping(const int64 ChainID, TSuccessCallback<bool> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "Ping", "", [this,OnSuccess](const FString& Content) {
		OnSuccess(this->BuildResponse<FPingReturn>(Content).status);
	}, OnFailure);
}

void UIndexer::Version(const int64 ChainID, TSuccessCallback<FVersion> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "Version", "", [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FVersionReturn>(Content).version);
	}, OnFailure);
}

void UIndexer::RunTimeStatus(const int64 ChainID, TSuccessCallback<FRuntimeStatus> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "RuntimeStatus", "", [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FRuntimeStatusReturn>(Content).status);
	}, OnFailure);
}

void UIndexer::GetChainID(const int64 ChainID, TSuccessCallback<int64> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "GetChainID", "", [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FGetChainIDReturn>(Content).chainID);
	}, OnFailure);
}

void UIndexer::GetEtherBalance(const int64 ChainID, FString AccountAddr, TSuccessCallback<FEtherBalance> OnSuccess, const FFailureCallback& OnFailure)
{//since we are given a raw accountAddress we compose the json arguments here to put in the request manually
	FString JSON_Arg = "{\"accountAddress\":\"";
	JSON_Arg.Append(AccountAddr);
	JSON_Arg.Append("\"}");

	HTTPPost(ChainID, "GetEtherBalance", JSON_Arg, [this,OnSuccess](const FString& Content)
	{
		const FGetEtherBalanceReturn Response = this->BuildResponse<FGetEtherBalanceReturn>(Content);
		OnSuccess(Response.balance);
	}, OnFailure);
}

void UIndexer::GetTokenBalances(const int64 ChainID, const FGetTokenBalancesArgs& Args, TSuccessCallback<FGetTokenBalancesReturn> OnSuccess, const FFailureCallback& OnFailure)
{
	const FString Endpoint = "GetTokenBalances";
	HTTPPost(ChainID, Endpoint, BuildArgs<FGetTokenBalancesArgs>(Args), [this,OnSuccess](const FString& Content)
	{
		const FGetTokenBalancesReturn Response = this->BuildResponse<FGetTokenBalancesReturn>(Content);
		OnSuccess(Response);
	}, OnFailure);
}

void UIndexer::GetTokenSupplies(const int64 ChainID, const FGetTokenSuppliesArgs& Args, TSuccessCallback<FGetTokenSuppliesReturn> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "GetTokenSupplies", BuildArgs<FGetTokenSuppliesArgs>(Args), [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FGetTokenSuppliesReturn>(Content));
	}, OnFailure);
}

void UIndexer::GetTokenSuppliesMap(const int64 ChainID, const FGetTokenSuppliesMapArgs& Args, TSuccessCallback<FGetTokenSuppliesMapReturn> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "GetTokenSuppliesMap", BuildArgs<FGetTokenSuppliesMapArgs>(Args), [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FGetTokenSuppliesMapReturn>(Content));
	}, OnFailure);
}

void UIndexer::GetBalanceUpdates(const int64 ChainID, const FGetBalanceUpdatesArgs& Args, TSuccessCallback<FGetBalanceUpdatesReturn> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "GetBalanceUpdates", BuildArgs<FGetBalanceUpdatesArgs>(Args), [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FGetBalanceUpdatesReturn>(Content));
	}, OnFailure);
}

void UIndexer::GetTransactionHistory(const int64 ChainID, const FGetTransactionHistoryArgs& Args, TSuccessCallback<FGetTransactionHistoryReturn> OnSuccess, const FFailureCallback& OnFailure)
{
	HTTPPost(ChainID, "GetTransactionHistory", BuildArgs<FGetTransactionHistoryArgs>(Args), [this,OnSuccess](const FString& Content)
	{
		OnSuccess(this->BuildResponse<FGetTransactionHistoryReturn>(Content));
	}, OnFailure);
}

TMap<int64, FTokenBalance> UIndexer::GetTokenBalancesAsMap(TArray<FTokenBalance> Balances)
{
	TMap<int64, FTokenBalance> BalanceMap;

	for (FTokenBalance Balance : Balances)
	{
		BalanceMap.Add(TPair<int64,FTokenBalance>(Balance.tokenID,Balance));
	}
	
	return BalanceMap;
}