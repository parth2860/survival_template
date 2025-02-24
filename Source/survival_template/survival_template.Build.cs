// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class survival_template : ModuleRules
{
	public survival_template(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
