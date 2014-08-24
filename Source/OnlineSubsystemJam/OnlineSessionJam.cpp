#include "OnlineSubsystemJam.h"
#include "OnlineSessionJam.h"
#include "OnlineSubsystemJamTypes.h"

bool FOnlineSessionJam::FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	bool ret = false;

	if (!CurrentSessionSearch.IsValid() && SearchSettings->SearchState != EOnlineAsyncTaskState::InProgress)
	{
		SearchSettings->SearchResults.Empty();

		if (SearchSettings->bIsLanQuery)
		{
			// LAN is harrrrrd
			return true;
		}
		else
		{
			// Make an HTTP Query
			CurrentSessionSearch = SearchSettings;
			SearchSettings->SearchState = EOnlineAsyncTaskState::InProgress;
			TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
			FString Value;
			GConfig->GetString(TEXT("OnlineSessionJam"), TEXT("HttpServerPrefix"), Value, GGameIni);
			HttpRequest->SetURL(Value + "/list");
			HttpRequest->SetVerb("GET");
			HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
			HttpRequest->OnProcessRequestComplete().BindRaw<FOnlineSessionJam>(this, &FOnlineSessionJam::ProcessListGetHttpRequest);
		}
	}
	else
	{
		UE_LOG_ONLINE(Warning, TEXT("Attempt to FindSessions while one is in progress"));
	}

	return ret;
}

void FOnlineSessionJam::ProcessListGetHttpRequest(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool unknown)
{
	FString ResponseContent = InResponse->GetContentAsString();
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseContent);
	FJsonSerializer::Deserialize(JsonReader, JsonArray);

	if (CurrentSessionSearch.IsValid())
	{
		for (TSharedPtr<FJsonValue> Value : JsonArray)
		{
			FOnlineSessionSearchResult* Result = new (CurrentSessionSearch->SearchResults) FOnlineSessionSearchResult();
			TSharedPtr<FJsonObject> JsObj = Value->AsObject();

			FString OutString;

			Result->Session.OwningUserName = JsObj->TryGetStringField("owner_name", OutString) ? OutString : "None";
			Result->Session.SessionInfo = MakeShareable<FOnlineSessionInfo>(new FOnlineSessionInfoJam());
			//CurrentSessionSearch->SearchResults.Add(MakeShareable(Result));
		}
		FOnlineSessionSearchResult Result;
		CurrentSessionSearch->SearchResults;
	}
}