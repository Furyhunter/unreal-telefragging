#pragma once

#include "GameFramework/GameState.h"
#include "DeathmatchGameState.generated.h"

UCLASS()
class TELEFRAGGER_API ADeathmatchGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(NetMulticast, Unreliable)
	void PlayerJoinedServer(const FString& PlayerName);

	UFUNCTION(NetMulticast, Unreliable)
	void PlayerLeftServer(const FString& PlayerName);
	
	UFUNCTION(NetMulticast, Unreliable)
	void PlayerChat(const FString& PlayerName, const FString& Message);
};