// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlightBrew : ModuleRules
{
	public BlightBrew(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" , "AssetRegistry" });

		//	AI DEPENDENCIES
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayTasks" });

		//  PARTICLE DEPENDENCIES
		PublicDependencyModuleNames.AddRange(new string[] { "Niagara" });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
