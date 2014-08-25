#include "Telefragger.h"
#include "DeathmatchHUD.h"
#include "DeathmatchPlayerState.h"
#include "DeathmatchGameState.h"

ADeathmatchHUD::ADeathmatchHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

int32 ADeathmatchHUD::GetPlayerScore()
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

void ADeathmatchHUD::SendChat(const FString& Message)
{
	// RPC call to gamestate
	GWorld->GetGameState<ADeathmatchGameState>()->PlayerChat(GetOwningPlayerController()->PlayerState->PlayerName, Message);
}