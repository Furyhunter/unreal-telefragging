#pragma once

#include "GameFramework/HUD.h"
#include "DeathmatchHUD.generated.h"

UCLASS()
class TELEFRAGGER_API ADeathmatchHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Game", meta = ( FriendlyName = "Get Player Score", Keywords = "get player score"))
	int32 GetPlayerScore();
};