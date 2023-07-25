// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Errors.h"
#include "General_Testing.generated.h"

UCLASS()
class SEQUENCEPLUGIN_API AGeneral_Testing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneral_Testing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//Testing Functions//

	/*
	* Called by frontend to test the provider!
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "Test_Provider")
		void test_provider();

	/*
	* Called by frontend to test the indexer
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "Test_Indexer")
		void test_indexer();
//End of Testing Functions//
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//These functions are for handling the callback pass and callback fail cases in testing!

	/*
	* Here I include some additional state_data about the callback that can be printed
	* in with the on successcallback!
	*/
	void callback_passed(FString state_data);

	/*
	* Here I include some additional state data about the callback as well as
	* error data that get printed out in the callback failure!
	*/
	void callback_failed(FString state_data, SequenceError error);

	/*
	* Used to convert an enum to a readable string
	*/
	FString error_to_string(ErrorType error);

};
