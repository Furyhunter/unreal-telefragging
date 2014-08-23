#include "Telefragger.h"
#include "DeathmatchHUD.h"
#include "DeathmatchPlayerState.h"

ADeathmatchHUD::ADeathmatchHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

uint32 ADeathmatchHUD::GetPlayerScore() const
{
	APlayerController* p = GetOwningPlayerController();
	if (p)
	{
		if (p->PlayerState)
		{
			return p->PlayerState->Score;
		}
	}

	// fallback
	return 0;
}