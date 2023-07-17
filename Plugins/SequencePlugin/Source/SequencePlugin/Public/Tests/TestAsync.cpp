#include "Misc/AutomationTest.h"
#include "Async.h"
#include "RequestHandler.h"

void Hello()
{
	UE_LOG(LogTemp, Display, TEXT("Hello world"));
}

void Print(FString Input)
{
	UE_LOG(LogTemp, Display, TEXT("I am printing %s"), *Input);
}

FString LateHello()
{
	FPlatformProcess::Sleep(3.0f);

	return "Hello World";
}

class MyClass
{
public:
	void MyPrint(FString Input)
	{
		UE_LOG(LogTemp, Display, TEXT("MyClass is printing %s"), *Input);
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsync, "Public.Tests.TestAsync",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsync::RunTest(const FString& Parameters)
{
	/*
	Async(EAsyncExecution::Thread, []
	{
		// code goes here
		auto Data = Async(EAsyncExecution::Thread, LateHello);
		Print(Data.Get());
	}).Wait();

	MyClass MyObject = MyClass();

	auto MyFuture = Async(EAsyncExecution::Thread, LateHello);
	TFunction<void (FString)> Func = [&MyObject](FString Input){MyObject.MyPrint(Input);};
	SendAsync(MyFuture, Func).Wait();*/

{
		Promise<FString> MyPromise{};
		
		auto Content = FJsonBuilder().ToPtr()
			->AddString("jsonrpc", "2.0")
			->AddInt("id", 1)
			->AddString("method", "eth_chainId")
			->ToString();
		
		auto Request = NewObject<URequestHandler>()
			->PrepareRequest()
			->WithUrl("http://localhost:8545/")
			->WithHeader("Content-type", "application/json")
			->WithVerb("POST")
			->WithContentAsString(Content)
			->GetRequest();

		Request->OnProcessRequestComplete().BindLambda([&MyPromise](FHttpRequestPtr Req, FHttpResponsePtr Response, bool IsSuccessful)
		{
			UE_LOG(LogTemp, Display, TEXT("Lambda called!"));
			if(IsSuccessful)
			{
				MyPromise.OnSuccess(Response->GetContentAsString());
			}
			else
			{
				MyPromise.OnFailure(Response);
			}
		});
		//Request->OnProcessRequestComplete().BindLambda([Number](FHttpRequestPtr Req, FHttpResponsePtr Response, bool IsSuccessful){1/Number;Hello();});
		Request->ProcessRequest();

		TFunction<int (FString)> Function = [](FString Content)
		{
			UE_LOG(LogTemp, Display, TEXT("I am loggin %s"), *Content);
			return 0;
		};
		MyPromise.Then<int>(Function).Get();
}
	
	// Make the test pass by returning true, or fail by returning false.
	return true;
}
