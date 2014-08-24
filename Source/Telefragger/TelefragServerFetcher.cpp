#include "Telefragger.h"
#include "TelefragServerFetcher.h"
#include "Json.h"

ATelefragServerFetcher::ATelefragServerFetcher(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{

}

void ATelefragServerFetcher::QueryServerList()
{
	if (bQuerying)
	{
		return;
	}
	bQuerying = true;
	TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(HttpServerAddress + "/list");
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	HttpRequest->OnProcessRequestComplete().BindUObject<ATelefragServerFetcher>(this, &ATelefragServerFetcher::HttpGetServersDelegate);
	HttpRequest->ProcessRequest();
}

void ATelefragServerFetcher::HttpGetServersDelegate(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	Results.Empty();

	if (!bWasSuccessful)
	{
		OnQueryCompleteDelegate.Broadcast();
		bQuerying = false;
		return;
	}
	
	FString ContentString = InResponse->GetContentAsString();
	TSharedPtr<FJsonObject> JsonBaseObject;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ContentString);
	FJsonSerializer::Deserialize(JsonReader, JsonBaseObject);
	const TArray<TSharedPtr<FJsonValue, ESPMode::NotThreadSafe>>& JsonArray = JsonBaseObject->GetArrayField("servers");

	
	
	for (int32 i = 0; i < JsonArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> Value = JsonArray[i];
		FServerFetcherResult Result;
		TSharedPtr<FJsonObject> JsObj = Value->AsObject();

		FString OutString;
		double OutNumber;

		Result.Name = JsObj->TryGetStringField("name", OutString) ? OutString : "Untitled Server";
		Result.URL = JsObj->TryGetStringField("url", OutString) ? OutString : "127.0.0.1";
		Result.GameVersion = JsObj->TryGetNumberField("version", OutNumber) ? FMath::RoundToInt(OutNumber) : 0;
		Result.Port = JsObj->TryGetNumberField("port", OutNumber) ? FMath::RoundToInt(OutNumber) : 7777;
		Results.Add(Result);
	}

	OnQueryCompleteDelegate.Broadcast();
	bQuerying = false;
}

bool ATelefragServerFetcher::IsQuerying()
{
	return bQuerying;
}

TArray<FServerFetcherResult, FDefaultAllocator>& ATelefragServerFetcher::GetResults()
{
	return Results;
}