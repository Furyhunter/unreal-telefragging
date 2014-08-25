#include "Telefragger.h"
#include "DeathmatchGameState.h"

ADeathmatchGameState::ADeathmatchGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> MessageSound(TEXT("SoundWave'/Game/Sounds/MessageBeep.MessageBeep'"));
	MessageWave = MessageSound.Object;
}

void ADeathmatchGameState::PlayerJoinedServer_Implementation(const FString& PlayerName)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::Cyan, FString::Printf(TEXT("%s has joined the server."), *PlayerName));
		if (MessageWave && GWorld && GWorld->GetFirstLocalPlayerFromController())
		{
			APlayerController* Controller = GWorld->GetFirstLocalPlayerFromController()->PlayerController;
			if (Controller != nullptr)
			{
				//Controller->ClientPlaySound(MessageWave, 1, 1);
			}
		}
	}
}

void ADeathmatchGameState::PlayerLeftServer_Implementation(const FString& PlayerName)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::Cyan, FString::Printf(TEXT("%s has left the server."), *PlayerName));
		if (MessageWave && GWorld && GWorld->GetFirstLocalPlayerFromController())
		{
			APlayerController* Controller = GWorld->GetFirstLocalPlayerFromController()->PlayerController;
			if (Controller != nullptr)
			{
				//Controller->ClientPlaySound(MessageWave, 1, 1);
			}
		}
	}
}

void ADeathmatchGameState::PlayerChat_Implementation(const FString& PlayerName, const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 10.f, FColor::White, FString::Printf(TEXT("%s: %s"), *PlayerName, *Message));
		if (MessageWave && GWorld && GWorld->GetFirstLocalPlayerFromController())
		{
			APlayerController* Controller = GWorld->GetFirstLocalPlayerFromController()->PlayerController;
			if (Controller != nullptr)
			{
				//Controller->ClientPlaySound(MessageWave, 1, 1);
			}
		}
	}
}
