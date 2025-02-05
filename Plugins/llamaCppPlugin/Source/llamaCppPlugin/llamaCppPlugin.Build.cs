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
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/llamaCpp")); }
	}

	private void LoadLlamaCpp(ReadOnlyTargetRules Target)
	{
		string LibrariesPath = Path.Combine(ThirdPartyPath, "Lib");
		string SharedLibDir = Path.Combine(ThirdPartyPath, "Binaries");
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Include"));
		PublicLibraryPaths.Add(LibrariesPath);
		PublicLibraryPaths.Add(SharedLibDir + "/Win64");


		//System.Console.WriteLine("SharedLibDir: " + SharedLibDir + "/Win64");
		//RuntimeDependencies.Add(SharedLibDir + "/Win64/llama.dll");
		//RuntimeDependencies.Add("ggml-base.dll");
		//RuntimeDependencies.Add("ggml-hip.dll");
		//RuntimeDependencies.Add("ggml-cpu.dll");
		//RuntimeDependencies.Add("ggml.dll");
		//RuntimeDependencies.Add("llama.dll");

		PublicDelayLoadDLLs.Add("ggml-base.dll");
		PublicDelayLoadDLLs.Add("ggml-hip.dll");
		PublicDelayLoadDLLs.Add("ggml-cpu.dll");
		PublicDelayLoadDLLs.Add("ggml.dll");
		PublicDelayLoadDLLs.Add("llama.dll");
		
		//PublicDelayLoadDLLs.Add(SharedLibDir + "\\Win64\\llama.dll");
		//foreach (string Dll in PublicDelayLoadDLLs)
		//{
		//	System.Console.WriteLine(Dll);
		//}
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "common.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "llama.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "ggml-base.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "ggml.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "ggml-hip.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "ggml-cpu.lib"));
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			//string SharedLibDirWin64 = Path.Combine(SharedLibDir, "Win64");
			
			//PublicLibraryPaths.Add(SharedLibDirWin64);
			//PublicDelayLoadDLLs.Add("C:/Users/ADMIN/Documents/Unreal Projects/UEllamaCpp/Plugins/llamaCppPlugin/Source/ThirdParty/llamaCpp/Binaries/Win64/llama.dll");
			//PublicDelayLoadDLLs.Add("C:/Users/ADMIN/Documents/Unreal Projects/UEllamaCpp/Plugins/llamaCppPlugin/Source/ThirdParty/llamaCpp/Binaries/Win64/ggml.dll");
			//PublicDelayLoadDLLs.Add("C:/Users/ADMIN/Documents/Unreal Projects/UEllamaCpp/Plugins/llamaCppPlugin/Source/ThirdParty/llamaCpp/Binaries/Win64/ggml-base.dll");
			//PublicDelayLoadDLLs.Add("C:/Users/ADMIN/Documents/Unreal Projects/UEllamaCpp/Plugins/llamaCppPlugin/Source/ThirdParty/llamaCpp/Binaries/Win64/ggml-hip.dll");
			//PublicDelayLoadDLLs.Add("C:/Users/ADMIN/Documents/Unreal Projects/UEllamaCpp/Plugins/llamaCppPlugin/Source/ThirdParty/llamaCpp/Binaries/Win64/ggml-cpu.dll");
			//PublicDe
			//RuntimeDependencies.Add(SharedLibDirWin64 + "/llama.dll");
			//RuntimeDependencies.Add(SharedLibDirWin64 + "/ggml.dll");
			//RuntimeDependencies.Add(SharedLibDirWin64 + "/ggml-base.dll");
			//RuntimeDependencies.Add(SharedLibDirWin64 + "/ggml-hip.dll");
			//RuntimeDependencies.Add(SharedLibDirWin64 + "/ggml-cpu.dll");
		}
	}

	public llamaCppPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		//Type = ModuleType.External;
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
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
		//LoadLlamaCpp(Target);
	}
}
