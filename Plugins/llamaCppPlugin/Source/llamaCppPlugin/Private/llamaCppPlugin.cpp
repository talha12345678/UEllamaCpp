// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "llamaCppPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
//#include "llamaCppPluginLibrary/llamaCpp/Include/llama.h"


#define LOCTEXT_NAMESPACE "FllamaCppPluginModule"

void FllamaCppPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("llamaCppPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/llamaCppPluginLibrary/x64/Release/LlamaCppHelperLib.dll"));
	//LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/llamaCppPluginLibrary/Win64/ExampleLibrary.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/llamaCppPluginLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	Model = nullptr;
	LlamaCppHelperLibHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (LlamaCppHelperLibHandle)
	{
		// Call the test function in the third party library that opens a message box
		LoadBackend();		
		LoadLLMModel("C:\\Users\\ADMIN\\Downloads\\DeepSeek-R1-Distill-Qwen-1.5B-Multilingual.i1-Q6_K.gguf", 99);
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}	
}

void FllamaCppPluginModule::LoadLLMModel(const FString& InModelPath, const int32 InNgl)
{
	auto Path = StringCast<ANSICHAR>(*InModelPath);
	Model = LoadModel(InNgl, Path.Get());
	if (Model)
	{
		UE_LOG(LogTemp, Error, TEXT("LlamaCpp: Model loaded"));
		//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Model loaded"));
		const llama_vocab* VocabModel = GetModelVocab(Model);
		//llama_token* Tokens = nullptr;
		TArray<llama_token> Tokens;
		int32_t NTokens = -TokenizePrompt(VocabModel, "What is your name ?", nullptr, 0);
		Tokens.AddZeroed(NTokens);
		//Tokens = new llama_token[NTokens]();
		auto Ret = TokenizePrompt(VocabModel, "What is your name ?", Tokens.GetData(), Tokens.Num());
		UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d Ret value"), Ret);
		if (Ret < 0)
		{
			UE_LOG(LogTemp, Error, TEXT("LlamaCpp: Unable to tokenize"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d valid tokens"), NTokens);
			//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "valid tokens"));
		}
		for (auto i : Tokens)
		{
			char buff[128];
			int32 r = PrintPromptByToken(VocabModel, i, buff);
			//FString s(buff);
			UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %s valid tokens"), *FString(buff));
			//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d valid tokens"), i);
		}
		//InitializeContext()
	}
}

void FllamaCppPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UnloadModel(Model);
	Model = nullptr;


	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LlamaCppHelperLibHandle);
	LlamaCppHelperLibHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FllamaCppPluginModule, llamaCppPlugin)
