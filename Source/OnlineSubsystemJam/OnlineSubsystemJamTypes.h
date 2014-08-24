#pragma once

#include "OnlineSubsystemJam.h"

class FOnlineSessionInfoJam : public FOnlineSessionInfo
{
protected:
	FOnlineSessionInfoJam(const FOnlineSessionInfoJam& Src)
	{
	}

	FOnlineSessionInfoJam& operator=(const FOnlineSessionInfoJam& Src)
	{
		return *this;
	}
public:
	
	TSharedPtr<class FInternetAddr> HostAddr = nullptr;
	FUniqueNetIdString SessionId;

	FOnlineSessionInfoJam() : SessionId("Test")
	{

	}

	virtual ~FOnlineSessionInfoJam()
	{

	}

	virtual const uint8* GetBytes() const override
	{
		return nullptr;
	}

	virtual int32 GetSize() const override
	{
		return sizeof(TSharedPtr<class FInernetAddr>)
			+ sizeof(SessionId.GetSize());
	}

	virtual bool IsValid() const override
	{
		return true;
	}

	virtual FString ToString() const override
	{
		return "Test";
	}

	virtual FString ToDebugString() const override
	{
		return "Test";
	}

	virtual const class FUniqueNetId& GetSessionId() const override
	{
		return SessionId;
	}

};