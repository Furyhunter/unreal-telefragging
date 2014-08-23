#include "Telefragger.h"
#include "DeathmatchGameMode.h"
#include "TelefraggerPlayerController.h"
#include "DeathmatchPlayerState.h"
#include "DeathmatchGameState.h"

ADeathmatchGameMode::ADeathmatchGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = ATelefraggerPlayerController::StaticClass();
	// TODO DefaultPawnClass =
	DefaultPlayerName = "Scrub";
	PlayerStateClass = ADeathmatchPlayerState::StaticClass();
	GameStateClass = ADeathmatchGameState::StaticClass();
}


