// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GOAP_5_4 : ModuleRules
{
	public GOAP_5_4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //core
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        //Ai dependencies
        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem" });

        //Gameplay Ability System dependencies
        PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
    }
}
