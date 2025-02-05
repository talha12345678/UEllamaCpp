// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class llamaCppPluginLibrary : ModuleRules
{
	public llamaCppPluginLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "x64", "Release"));
			PublicAdditionalLibraries.Add("ExampleLibrary.lib");

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("ExampleLibrary.dll");

			//include
			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "llamaCpp", "Include"));

			//libs
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "x64"));
			//PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "llamaCpp", "Lib"));
			PublicLibraryPaths.Add("C:/Program Files/AMD/ROCm/6.1/lib");
		

			PublicAdditionalLibraries.Add("libomp.lib");
			PublicAdditionalLibraries.Add("amdhip64.lib");
			PublicAdditionalLibraries.Add("rocblas.lib");
			PublicAdditionalLibraries.Add("hipblas.lib");
			//PublicAdditionalLibraries.Add("libiomp5md.lib");
			PublicAdditionalLibraries.Add("common.lib");
			PublicAdditionalLibraries.Add("llama.lib");
			PublicAdditionalLibraries.Add("ggml-base.lib");
			PublicAdditionalLibraries.Add("ggml.lib");
			PublicAdditionalLibraries.Add("ggml-hip.lib");
			PublicAdditionalLibraries.Add("ggml-cpu.lib");


			//dlls
			//PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "llamaCpp", "Binaries", "Win64"));
			//string DllPath = Path.Combine(ModuleDirectory, "x64");
			//PublicLibraryPaths.Add(DllPath);

			//PublicDelayLoadDLLs.Add("llava_shared.dll");
			//PublicDelayLoadDLLs.Add("ggml-base.dll");
			//PublicDelayLoadDLLs.Add("ggml-hip.dll");
			//PublicDelayLoadDLLs.Add("ggml-cpu.dll");

			//RuntimeDependencies.Add(Path.Combine(DllPath, "llama.dll"));
			//RuntimeDependencies.Add(Path.Combine(DllPath, "ggml.dll"));
			//c:\windows\system32\MSVCP140.DLL
			//PublicDelayLoadDLLs.Add("MSVCP140.dll");
			//c:\windows\system32\VCRUNTIME140.DLL
			//PublicDelayLoadDLLs.Add("VCRUNTIME140.dll");
			//PublicDelayLoadDLLs.Add("ggml-base.dll");
			//PublicDelayLoadDLLs.Add("ggml-hip.dll");
			//PublicDelayLoadDLLs.Add("ggml-cpu.dll");
			///PublicDelayLoadDLLs.Add("llama.dll");
			//PublicDelayLoadDLLs.Add("ggml.dll");
			


		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
        }		
	}
}
