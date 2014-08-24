#include "OnlineSubsystemJam.h"
#include "OnlineSubsystemJamModule.h"
#include "ModuleManager.h"

IMPLEMENT_MODULE(FOnlineSubsystemJamModule, OnlineSubsystemJam);

class FOnlineFactoryJam : public IOnlineFactory
{
private:
	static FOnlineSubsystemJamPtr JamSingleton;

	virtual void DestroySubsystem()
	{
		if (JamSingleton.IsValid())
		{
			JamSingleton->Shutdown();
			JamSingleton = nullptr;
		}
	}
public:
	FOnlineFactoryJam() {}
	virtual ~FOnlineFactoryJam()
	{
		DestroySubsystem();
	}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
	{
		if (!JamSingleton.IsValid())
		{
			JamSingleton = MakeShareable(new FOnlineSubsystemJam(InstanceName));
			if (JamSingleton->IsEnabled())
			{
				if (!JamSingleton->Init())
				{
					UE_LOG_ONLINE(Warning, TEXT("Jam online system failed to initialize."));
					DestroySubsystem();
				}
			}
			else
			{
				UE_LOG_ONLINE(Warning, TEXT("Jam online subsystem is disabled."));
				DestroySubsystem();
			}
			return JamSingleton;
		}

		UE_LOG_ONLINE(Warning, TEXT("Can't create more than one instance of Jam online subsystem."));
		return nullptr;
	}
};

FOnlineSubsystemJamPtr FOnlineFactoryJam::JamSingleton = nullptr;

void FOnlineSubsystemJamModule::StartupModule()
{
	JamFactory = new FOnlineFactoryJam();

	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService("Jam", JamFactory);
}

void FOnlineSubsystemJamModule::ShutdownModule()
{
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService("Jam");

	delete JamFactory;
	JamFactory = nullptr;
}