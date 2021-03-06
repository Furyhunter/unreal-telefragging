#include "Telefragger.h"
#include "DeathmatchGameMode.h"
#include "TelefraggerPlayerController.h"
#include "DeathmatchPlayerState.h"
#include "DeathmatchGameState.h"
#include "DeathmatchHUD.h"
#include "Http.h"

ADeathmatchGameMode::ADeathmatchGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/PlayerCharacter_BP.PlayerCharacter_BP'"));
	if (PlayerPawnObject.Object != nullptr)
	{
		DefaultPawnClass = (UClass*) PlayerPawnObject.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> PlayerControllerObject(TEXT("Blueprint'/Game/Blueprints/TelefraggerPlayerController_BP.TelefraggerPlayerController_BP'"));
	if (PlayerPawnObject.Object != nullptr)
	{
		PlayerControllerClass = (UClass*) PlayerControllerObject.Object->GeneratedClass;
	}
	DefaultPlayerName = "Scrubmaster";
	PlayerStateClass = ADeathmatchPlayerState::StaticClass();
	GameStateClass = ADeathmatchGameState::StaticClass();

	ConstructorHelpers::FObjectFinder<UBlueprint> HUDObject(TEXT("Blueprint'/Game/Blueprints/DeathmatchHUD_BP.DeathmatchHUD_BP'"));
	if (HUDObject.Object != nullptr)
	{
		HUDClass = (UClass*)HUDObject.Object->GeneratedClass;
	}

	bool bSendingHeartbeat = false;
	
}

void ADeathmatchGameMode::SendHeartbeatToMS()
{
	TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	FString Value;
	GConfig->GetString(TEXT("/Script/Telefragger.TelefragServerFetcher"), TEXT("HttpServerAddress"), Value, GGameIni);

	FString ServerName = "Test";
	if (GWorld)
	{
		ServerName = GWorld->GetFirstLocalPlayerFromController()->PlayerController->PlayerState->PlayerName;
	}
	HttpRequest->SetURL(Value + "/heartbeat");
	HttpRequest->SetContentAsString("name=" + ServerName + "'s%20Server");
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	HttpRequest->SetVerb("POST");
	HttpRequest->ProcessRequest();
	// fire and forget... doesn't really matter to us if it succeeds
}

void ADeathmatchGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if (GWorld && GWorld->IsServer() && !GWorld->IsPlayInEditor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Heartbeat enabled"));
		GetWorldTimerManager().SetTimer(this, &ADeathmatchGameMode::SendHeartbeatToMS, 4.f, true, 4.f);
		bSendingHeartbeat = true;
	}

	GameSession->MaxPlayers = 16;
}

void ADeathmatchGameMode::HandleLeavingMap()
{
	// clear the timer before it tries to heartbeat again...
	if (bSendingHeartbeat)
	{
		// Deregister with the MS.
		GetWorldTimerManager().ClearTimer(this, &ADeathmatchGameMode::SendHeartbeatToMS);

		TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		FString Value;
		GConfig->GetString(TEXT("/Script/Telefragger.TelefragServerFetcher"), TEXT("HttpServerAddress"), Value, GGameIni);
		HttpRequest->SetURL(Value + "/remove");
		HttpRequest->SetVerb("POST");
		HttpRequest->ProcessRequest(); // fire and forget!
	}
}

APlayerController* ADeathmatchGameMode::Login(UPlayer* NewPlayer, const FString& Portal, const FString& Options, const TSharedPtr<FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	auto ret = Super::Login(NewPlayer, Portal, Options, UniqueId, ErrorMessage);

	// Tell clients with an RPC
	GetGameState<ADeathmatchGameState>()->PlayerJoinedServer(ret->PlayerState->PlayerName);

	return ret;
}

void ADeathmatchGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// Tell clients with RPC
	GetGameState<ADeathmatchGameState>()->PlayerLeftServer(Exiting->PlayerState->PlayerName);
}

bool ADeathmatchGameMode::ReadyToEndMatch()
{
	int32 highest = 0;
	APlayerState* Winner = nullptr;
	for (APlayerState* P : GameState->PlayerArray)
	{
		Winner = highest >= P->Score ? Winner : P;
		highest = highest >= P->Score ? highest : FMath::RoundToInt(P->Score);
	}

	if (highest > 10)
	{
		return true;
	}
	return false;
}