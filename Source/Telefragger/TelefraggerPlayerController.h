

#pragma once

#include "GameFramework/PlayerController.h"
#include "TelefraggerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TELEFRAGGER_API ATelefraggerPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()


	UFUNCTION( BlueprintCallable, Category=Respawn)
	void Respawn();
};
