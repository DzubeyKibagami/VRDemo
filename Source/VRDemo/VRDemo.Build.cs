using UnrealBuildTool;

public class VRDemo : ModuleRules
{
	public VRDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "XRBase", "HeadMountedDisplay", "Niagara", "NavigationSystem" });
	}
}
