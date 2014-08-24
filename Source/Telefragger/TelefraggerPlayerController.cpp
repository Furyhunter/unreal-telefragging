

#include "Telefragger.h"
#include "TelefraggerPlayerController.h"


ATelefraggerPlayerController::ATelefraggerPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ATelefraggerPlayerController::Respawn()
{
	APlayerController::ServerRestartPlayer();
}

