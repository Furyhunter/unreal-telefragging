#pragma once

#include "GameFramework/HUD.h"
#include "DeathmatchHUD.generated.h"

UCLASS()
class TELEFRAGGER_API ADeathmatchHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
public:
	uint32 GetPlayerScore() const;
};