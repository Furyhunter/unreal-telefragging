

using UnrealBuildTool;

public class OnlineSubsystemJam : ModuleRules
{
	public OnlineSubsystemJam(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "OnlineSubsystemUtils", "HTTP" });

		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
	}
}
