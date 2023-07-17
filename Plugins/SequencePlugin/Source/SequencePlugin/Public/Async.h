#pragma once

#include "Errors.h"
#include "Provider.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Interfaces/IHttpRequest.h"

template <typename T>
TFuture<void> SendAsync(TFuture<T>& Input, TFunction<void (T)>& CallBack)
{
	return Async(EAsyncExecution::Thread, [&Input, &CallBack]()
	{
		CallBack(Input.Get());
	});
}

template <typename TIn, typename TOut>
TFuture<TOut> PipeAsync(TFuture<TIn>& Input, TFunction<TOut (TIn)>& TransformFunction)
{
	return Async(EAsyncExecution::Thread, [&Input, &TransformFunction]
	{
		return TransformFunction(Input.Get());
	});
}

enum class PromiseStatus
{
	Pending,
	Fulfilled,
	Rejected,
};

constexpr double GNo_Max_Wait_Time = -1;

template <typename T>
struct Promise
{
	PromiseStatus Status = PromiseStatus::Pending;
	TFunction<void (T)> Callback = nullptr;
	bool HasCallback = false;
	FHttpResponsePtr ResponsePtr = nullptr;
	T Value;
	
	TFunction<void (T)> GetOnSuccessCallback()
	{
		return [this](T Input){ this->OnSuccess(Input); };
	}

	TFunction<void (FHttpResponsePtr)> GetOnFailureCallback()
	{
		return [this](FHttpResponsePtr Response)
		{
			this->ResponsePtr = Response;
			this->Status = PromiseStatus::Rejected;
		};
	}

	void OnSuccess(T ReturnValue)
	{
		this->Value = ReturnValue;
		
		this->Status = PromiseStatus::Fulfilled;
		
		if(HasCallback)
		{
			Callback(Value);
		}
	}

	void OnFailure(FHttpResponsePtr Response)
	{
		this->Status = PromiseStatus::Rejected;
	}

	TResult<T> Get(double MaxWaitTime = GNo_Max_Wait_Time)
	{
		double StartTime = FPlatformTime::Seconds();
		while (Status == PromiseStatus::Pending)
		{
			FPlatformProcess::Sleep(0.25f);
			const double AppTime = FPlatformTime::Seconds();
			if(MaxWaitTime != GNo_Max_Wait_Time && AppTime - StartTime >= MaxWaitTime)
			{
				Status = PromiseStatus::Rejected;
				return MakeError(SequenceError(RequestTimeExceeded, "Await Time Exceeded!"));
			}
		}

		Status = PromiseStatus::Fulfilled;
		return MakeValue(Value);
	}

	template<typename TReturn>
	Promise<TReturn> Then(TFunction<TReturn (T)> Consumer)
	{
		auto NextPromise = Promise<TReturn>();
		Callback = [this, &NextPromise, &Consumer](T Input)
		{
			TReturn Output = Consumer(Value);
			NextPromise.OnSuccess(Output);
		};
		HasCallback = true;
		
		if(Status == PromiseStatus::Fulfilled)
		{
			Callback(Value);
		}
		else if(Status == PromiseStatus::Rejected)
		{
			NextPromise.ResponsePtr = this->ResponsePtr;
			NextPromise.Status = PromiseStatus::Rejected;
		}

		return NextPromise;
	}
};