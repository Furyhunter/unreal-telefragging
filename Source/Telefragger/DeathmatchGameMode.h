

#pragma once

#include "GameFramework/GameMode.h"
#include "DeathmatchGameMode.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class TELEFRAGGER_API ADeathmatchGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	bool bAnnounced;

	UPROPERTY(Config)
	bool bAlwaysAnnounced;

	UFUNCTION(BlueprintCallable, Category = "Online")
	void SendHeartbeatToMS();

	UPROPERTY()
	bool bSendingHeartbeat;

	virtual void HandleLeavingMap() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
