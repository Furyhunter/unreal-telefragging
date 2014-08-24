#pragma once

#include "OnlineSubsystemJam.h"
#include "Core.h"
#include "ModuleInterface.h"

class FOnlineSubsystemJamModule : public IModuleInterface
{
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