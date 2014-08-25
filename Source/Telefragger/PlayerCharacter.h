

#pragma once

#include "GameFramework/Character.h"
#include "ParticleSystemComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TELEFRAGGER_API APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category=fuck)
	void SetParticleParameter(UParticleSystemComponent* system, float value);	
	
};
