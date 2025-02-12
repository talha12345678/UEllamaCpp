// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;
using Microsoft.Win32;
using System.Diagnostics;
using Tools.DotNETCommon;




public class llamaCppPlugin : ModuleRules
{
	public llamaCppPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//string ThirdPartyPath = Path.Combine(ModuleDirectory, "../", "ThirdParty");
		//string LlamaIncludePath = Path.Combine(ThirdPartyPath, "llamaCppPluginLibrary", "llamaCpp", "Include");
		//System.Console.WriteLine("LlamaIncludePath: " + LlamaIncludePath);
		//PublicIncludePaths.Add(LlamaIncludePath);

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...				
				//"../ThirdParty/llamaCppPluginLibrary/llamaCpp/Include"
				//"./ThirdParty/llamaCppPluginLibrary/llamaCpp/Include"
				//"./ThirdParty/llamaCppPluginLibrary"

			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...				
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"llamaCppPluginLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...				
			}
			);		
	}
}
