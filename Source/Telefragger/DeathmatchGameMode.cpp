#include "Telefragger.h"
#include "DeathmatchGameMode.h"
#include "TelefraggerPlayerController.h"
#include "DeathmatchPlayerState.h"
#include "DeathmatchGameState.h"

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
}


