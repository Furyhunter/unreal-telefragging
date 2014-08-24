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
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/PlayerCharacter_BP.PlayerCharacter_BP'"));
	if (PlayerPawnObject.Object != nullptr)
	{
		DefaultPawnClass = (UClass*) PlayerPawnObject.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerControllerObject(TEXT("Blueprint'/Game/Blueprints/TelefraggerPlayerController_BP.TelefraggerPlayerController_BP'"));
	if (PlayerPawnObject.Object != nullptr)
	{
		PlayerControllerClass = (UClass*) PlayerControllerObject.Object->GeneratedClass;
	}
	DefaultPlayerName = "Scrub";
	PlayerStateClass = ADeathmatchPlayerState::StaticClass();
	GameStateClass = ADeathmatchGameState::StaticClass();
	HUDClass = ADeathmatchHUD::StaticClass();
}

void ADeathmatchGameMode::SendHeartbeatToMS()
{
	TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	FString Value;
	GConfig->GetString(TEXT("/Script/Telefragger.TelefragServerFetcher"), TEXT("HttpServerAddress"), Value, GGameIni);
	HttpRequest->SetURL(Value + "/heartbeat");
	HttpRequest->SetContentAsString(TEXT("name=Test"));
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	HttpRequest->SetVerb("POST");
	HttpRequest->ProcessRequest();
	// fire and forget... doesn't really matter to us if it succeeds
}

void ADeathmatchGameMode::HandleLeavingMap()
{
	// clear the timer before it tries to heartbeat again...
	GetWorldTimerManager().ClearTimer(this, &ADeathmatchGameMode::SendHeartbeatToMS);

	TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	FString Value;
	GConfig->GetString(TEXT("/Script/Telefragger.TelefragServerFetcher"), TEXT("HttpServerAddress"), Value, GGameIni);
	HttpRequest->SetURL(Value + "/remove");
	HttpRequest->SetVerb("POST");
	HttpRequest->ProcessRequest(); // fire and forget!
}

void ADeathmatchGameMode::HandleMatchIsWaitingToStart()
{
	if (GWorld && !GWorld->IsPlayInEditor() && !GWorld->IsPlayInMobilePreview() && !GWorld->IsPlayInPreview() && !GetWorldTimerManager().TimerExists(this, &ADeathmatchGameMode::SendHeartbeatToMS))
	{
		GetWorldTimerManager().SetTimer(this, &ADeathmatchGameMode::SendHeartbeatToMS, 4.f, true, 4.f);
	}
}