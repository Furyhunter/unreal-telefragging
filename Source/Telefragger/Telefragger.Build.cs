

using UnrealBuildTool;

public class Telefragger : ModuleRules
{
	public Telefragger(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HTTP" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
