// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUnrealProject : ModuleRules
{
	public MyUnrealProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
