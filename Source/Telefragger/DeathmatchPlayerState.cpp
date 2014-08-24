#include "Telefragger.h"
#include "DeathmatchPlayerState.h"

ADeathmatchPlayerState::ADeathmatchPlayerState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ADeathmatchPlayerState::IncrementScore()
{
	APlayerState::Score += 1.0f;
}
