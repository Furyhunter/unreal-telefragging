#pragma once

#include "Http.h"
#include "TelefragServerFetcher.generated.h"

USTRUCT(BlueprintType)
struct TELEFRAGGER_API FServerFetcherResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Online")
	FString Name;
	UPROPERTY(BlueprintReadOnly, Category = "Online")
	FString URL;
	UPROPERTY(BlueprintReadOnly, Category = "Online")
	int32 GameVersion;
	UPROPERTY(BlueprintReadOnly, Category = "Online")
	int32 Port;
};

UCLASS(Config=Game)
class TELEFRAGGER_API ATelefragServerFetcher : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Online", meta = (FriendlyName = "Query Server List"))
	void QueryServerList();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQueryComplete);

	UPROPERTY(BlueprintAssignable, Category = "Online", meta = (FriendlyName = "On Query Complete Delegate"))
	FOnQueryComplete OnQueryCompleteDelegate;

	UFUNCTION(BlueprintPure, Category = "Online", meta = (FriendlyName = "Get Is Querying"))
	bool IsQuerying();

	UPROPERTY(BlueprintReadOnly, Config, Category = "Online")
	int32 CurrentGameVersion;

	UFUNCTION(BlueprintCallable, Category = "Online", meta = (FriendlyName = "Get Query Search Results"))
	TArray<FServerFetcherResult>& GetResults();

	UPROPERTY(Config)
	FString HttpServerAddress;
private:
	TArray<FServerFetcherResult> Results;
	bool bQuerying;

	void HttpGetServersDelegate(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful);
};
