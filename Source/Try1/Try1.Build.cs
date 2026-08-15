// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Try1 : ModuleRules
{
	public Try1(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Try1",
			"Try1/Variant_Platforming",
			"Try1/Variant_Platforming/Animation",
			"Try1/Variant_Combat",
			"Try1/Variant_Combat/AI",
			"Try1/Variant_Combat/Animation",
			"Try1/Variant_Combat/Gameplay",
			"Try1/Variant_Combat/Interfaces",
			"Try1/Variant_Combat/UI",
			"Try1/Variant_SideScrolling",
			"Try1/Variant_SideScrolling/AI",
			"Try1/Variant_SideScrolling/Gameplay",
			"Try1/Variant_SideScrolling/Interfaces",
			"Try1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
