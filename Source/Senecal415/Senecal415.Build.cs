// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Senecal415 : ModuleRules
{
	public Senecal415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
