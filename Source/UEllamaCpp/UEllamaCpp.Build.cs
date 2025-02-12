// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class UEllamaCpp : ModuleRules
{
	public UEllamaCpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		//string ThirdPartyPath = Path.Combine(ModuleDirectory, "../", "../", "Plugins", "llamaCppPlugin", "Source", "ThirdParty");
		//string LlamaIncludePath = Path.Combine(ThirdPartyPath, "llamaCppPluginLibrary", "llamaCpp", "Include");
		//string LlamaIncludePath = Path.Combine(ThirdPartyPath, "llamaCppPluginLibrary");
		//System.Console.WriteLine("LlamaIncludePath: " + LlamaIncludePath);
		//PublicIncludePaths.Add(LlamaIncludePath);


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
