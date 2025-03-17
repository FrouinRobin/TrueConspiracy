// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TrueConspiracy : ModuleRules
{
	public TrueConspiracy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore",
            "NavigationSystem", "AIModule", "Niagara", "EnhancedInput",
            "UMG", "SlateCore", "GameplayTags", "GameplayTasks", "TextureUtilitiesCommon"
        });
    }
}
