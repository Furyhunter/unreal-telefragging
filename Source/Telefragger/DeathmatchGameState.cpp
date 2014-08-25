#include "Telefragger.h"
#include "DeathmatchGameState.h"

ADeathmatchGameState::ADeathmatchGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void ADeathmatchGameState::PlayerJoinedServer_Implementation(const FString& PlayerName)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::Cyan, FString::Printf(TEXT("%s has joined the server."), *PlayerName));
	}
}

void ADeathmatchGameState::PlayerLeftServer_Implementation(const FString& PlayerName)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::Cyan, FString::Printf(TEXT("%s has left the server."), *PlayerName));
	}
}

void ADeathmatchGameState::PlayerChat_Implementation(const FString& PlayerName, const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::White, FString::Printf(TEXT("%s: %s"), *PlayerName, *Message));
	}
}
