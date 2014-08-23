

#include "Telefragger.h"
#include "TelefraggerGameMode.h"
#include "TelefraggerPlayerController.h"

ATelefraggerGameMode::ATelefraggerGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = ATelefraggerPlayerController::StaticClass();
}


