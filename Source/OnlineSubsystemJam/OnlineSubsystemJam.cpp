#include "OnlineSubsystemJam.h"
#include "OnlineSessionJam.h"

IOnlineSessionPtr FOnlineSubsystemJam::GetSessionInterface() const
{
	return SessionInterface;
}

bool FOnlineSubsystemJam::Init()
{
	SessionInterface = MakeShareable(new FOnlineSessionJam());
	return true;
}

bool FOnlineSubsystemJam::IsEnabled() const
{
	return true;
}