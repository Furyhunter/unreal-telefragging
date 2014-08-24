#pragma once

#include "OnlineSubsystemJam.h"
#include "Core.h"
#include "ModuleInterface.h"

class FOnlineSubsystemJamModule : public IModuleInterface
{
private:
	class FOnlineFactoryJam* JamFactory = nullptr;
public:
	FOnlineSubsystemJamModule() {}
	virtual ~FOnlineSubsystemJamModule() {}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}

	virtual bool SupportsAutomaticShutdown() override
	{
		return false;
	}
};