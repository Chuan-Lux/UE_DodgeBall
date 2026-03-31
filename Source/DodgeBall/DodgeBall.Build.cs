// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DodgeBall : ModuleRules
{
	public DodgeBall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DodgeBall",
			"DodgeBall/Variant_Platforming",
			"DodgeBall/Variant_Platforming/Animation",
			"DodgeBall/Variant_Combat",
			"DodgeBall/Variant_Combat/AI",
			"DodgeBall/Variant_Combat/Animation",
			"DodgeBall/Variant_Combat/Gameplay",
			"DodgeBall/Variant_Combat/Interfaces",
			"DodgeBall/Variant_Combat/UI",
			"DodgeBall/Variant_SideScrolling",
			"DodgeBall/Variant_SideScrolling/AI",
			"DodgeBall/Variant_SideScrolling/Gameplay",
			"DodgeBall/Variant_SideScrolling/Interfaces",
			"DodgeBall/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
