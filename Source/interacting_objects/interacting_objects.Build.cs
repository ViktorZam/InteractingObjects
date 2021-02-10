// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class interacting_objects : ModuleRules
{
	public interacting_objects(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
