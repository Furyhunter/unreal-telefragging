#pragma once

#include "OnlineSessionInterface.h"
#include "OnlineSubsystemJam.h"

class FOnlineSessionJam : public IOnlineSession
{
private:
	class FOnlineSubsystemJam* JamSubsystem;
protected:
	class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override { return nullptr; }
	class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override { return nullptr; }
public:
	virtual ~FOnlineSessionJam() {}

	FNamedOnlineSession* GetNamedSession(FName SessionName) override { return nullptr; }
	void RemoveNamedSession(FName SessionName) override {}
	bool HasPresenceSession() override { return false; }
	EOnlineSessionState::Type GetSessionState(FName SessionName) const override { return EOnlineSessionState::NoSession; }
	bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override { return false; }
	bool StartSession(FName SessionName) override { return false; }
	bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override { return false; }
	bool EndSession(FName SessionName) override { return false; }
	bool DestroySession(FName SessionName) override { return false; }
	bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override { return false; }
	bool StartMatchmaking(int32 SearchingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override { return false; }
	bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override { return false; }
	bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) { return false; }
	bool CancelFindSessions() override { return false; }
	bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override { return false; }
	bool JoinSession(int32 LocalUserNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) { return false; }
	bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override { return false; }
	bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override { return false; }
	bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< TSharedRef<FUniqueNetId> >& Friends) override { return false; }
	bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo) override { return false; }
	bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override { return false; }
	FOnlineSessionSettings* GetSessionSettings(FName SessionName) override { return nullptr; }
	bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override { return false; }
	bool RegisterPlayers(FName SessionName, const TArray< TSharedRef<class FUniqueNetId> >& Players, bool bWasInvited = false) override { return false; }
	bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override { return false; }
	bool UnregisterPlayers(FName SessionName, const TArray< TSharedRef<class FUniqueNetId> >& Players) override { return false; }
	int32 GetNumSessions() override { return 0; }
	void DumpSessionState() override {}

};
