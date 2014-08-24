#pragma once

#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"

typedef TSharedPtr<class FOnlineSubsystemJam, ESPMode::ThreadSafe> FOnlineSubsystemJamPtr;

class ONLINESUBSYSTEMJAM_API FOnlineSubsystemJam : public FOnlineSubsystemImpl, public FTickerObjectBase
{
public:
	FOnlineSubsystemJam(FName InInstanceName)
	{
		
	}
	virtual ~FOnlineSubsystemJam() {}

	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override { return nullptr; }
	virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override { return nullptr; }
	virtual IOnlineUserCloudPtr GetUserCloudInterface() const override { return nullptr; }
	virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override { return nullptr; }
	virtual IOnlineVoicePtr GetVoiceInterface() const override { return nullptr; }
	virtual IOnlineExternalUIPtr GetExternalUIInterface() const override { return nullptr; }
	virtual IOnlineTimePtr GetTimeInterface() const override { return nullptr; }
	virtual IOnlineIdentityPtr GetIdentityInterface() const override { return nullptr; }
	virtual IOnlinePartyPtr GetPartyInterface() const override { return nullptr; }
	virtual IOnlineTitleFilePtr GetTitleFileInterface() const override { return nullptr; }
	virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override { return nullptr; }
	virtual IOnlineStorePtr GetStoreInterface() const override { return nullptr; }
	virtual IOnlineEventsPtr GetEventsInterface() const override { return nullptr; }
	virtual IOnlineAchievementsPtr GetAchievementsInterface() const override { return nullptr; }
	virtual IOnlineSharingPtr GetSharingInterface() const override { return nullptr; }
	virtual IOnlineUserPtr GetUserInterface() const override { return nullptr; }
	virtual IOnlineMessagePtr GetMessageInterface() const override { return nullptr; }
	virtual IOnlinePresencePtr GetPresenceInterface() const override { return nullptr; }
	virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const override { return false; }
	virtual bool Init() override { return false; }
	virtual bool Shutdown() override { return false; }
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override { return true; }
	bool IsEnabled() const { return false; }
	virtual bool IsServer() const override { return false; }
	virtual void SetForceDedicated(bool bForce) override { }
	FString GetAppId() const override { return "Jam"; }

	bool Tick(float Delta) override { return true; }
};