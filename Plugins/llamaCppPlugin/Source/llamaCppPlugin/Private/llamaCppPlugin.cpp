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

	Model_ = nullptr;
	Ctx_ = nullptr;
	Smpl_ = nullptr;
	LlamaCppHelperLibHandle_ = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (LlamaCppHelperLibHandle_)
	{
		// Call the test function in the third party library that opens a message box
		LoadBackend();		
		LoadLLMModel("C:\\Users\\ADMIN\\Downloads\\DeepSeek-R1-Distill-Qwen-1.5B-Multilingual.i1-Q6_K.gguf", 99, "Hello my name is");
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}	
}



static void log_callback(ggml_log_level level, const char* fmt, void* data)
{
	FString Fmt(fmt);
	//UE_LOG(LogTemp, Error, TEXT("%s"), *Fmt);
	switch (level)
	{
		case GGML_LOG_LEVEL_ERROR:
			UE_LOG(LlamaCpp, Error, TEXT("%s"), *Fmt);
			break;
		case GGML_LOG_LEVEL_WARN:
			UE_LOG(LlamaCpp, Warning, TEXT("%s"), *Fmt);
			break;
		default:
			UE_LOG(LlamaCpp, Display, TEXT("%s"), *Fmt);
			break;
	}	
}

//static_assert(TIsPointer<decltype(InToken), llama_token>::Value, "InToken must llama_token*"); \	
// static_assert(TIsSame<decltype(InToken), llama_token*>::Value, "InToken must be a llama_token*"); \
//static_assert(TIsSame<decltype(InNTokens), int32_t>::Value, "InToken must be a llama_token*"); \

#define NextBatch(InToken, InNTokens) TIsSame<decltype(InToken), llama_token*>::Value && TIsSame<decltype(InNTokens), int32_t>::Value ? InitializeBatch(InToken, InNTokens) : llama_batch();
 

//constexpr llama_batch NxtBatch(llama_token* InToken, int32_t InNTokens)
//{
	//llama_batch LBatch = InitializeBatch(InToken, InNTokens);
	//return LBatch;
//}

void FllamaCppPluginModule::LoadLLMModel(const FString& InModelPath, const int32 InNgl, const FString& InPrompt)
{
	//TIsSame<
	int32_t n_predict = 32;
	LogSet(log_callback, nullptr);
	auto Path = StringCast<ANSICHAR>(*InModelPath);
	auto Prompt = StringCast<ANSICHAR>(*InPrompt);
	Model_ = LoadModel(InNgl, Path.Get());
	if (Model_)
	{
		//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: Model loaded"));
		//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Model loaded"));
		const llama_vocab* VocabModel = GetModelVocab(Model_);
		//llama_token* Tokens = nullptr;
		TArray<llama_token> Tokens;
		int32_t NTokens = -TokenizePrompt(VocabModel, Prompt.Get(), nullptr, 0);
		Tokens.AddZeroed(NTokens);
		//Tokens = new llama_token[NTokens]();
		auto Ret = TokenizePrompt(VocabModel, Prompt.Get(), Tokens.GetData(), Tokens.Num());
		//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d Ret value"), Ret);
		if (Ret < 0)
		{
			//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: Unable to tokenize"));
		}
		else
		{
			//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d valid tokens"), NTokens);
			
			
			Ctx_ = InitializeContext(NTokens, n_predict, Model_);
			if (Ctx_)
			{
				//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: Valid context"));
			}
			//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "valid tokens"));
		}
		for (auto i : Tokens)
		{
			char buff[128];
			int32 r = PrintPromptByToken(VocabModel, i, buff);
			//FString s(buff);
			//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %s valid tokens"), *FString(buff));
			//UE_LOG(LogTemp, Error, TEXT("LlamaCpp: %d valid tokens"), i);
		}
		Smpl_ = InitializeSampler(false);
		if (Smpl_)
		{
			
		}
		Batch_ = InitializeBatch(Tokens.GetData(), Tokens.Num());
		
		int NOfDecode = 0;
		llama_token NewTokenId;
		std::string Op;
		for (int n_pos = 0; n_pos + Batch_.n_tokens < NTokens + n_predict;)
		{
			if (Decode(Ctx_, Batch_)) 
			{
				break;
			}
			n_pos += Batch_.n_tokens;
			{
				NewTokenId = Sample(Smpl_, Ctx_, -1);

				if (IsEog(VocabModel, NewTokenId)) {
					break;
				}

				char buff[128];
				int32 r = PrintPromptByToken(VocabModel, NewTokenId, buff);
				std::string Str(buff, r);
				//FString Str(buff);
				Op += Str;
				//FString()
				//log_callback(GGML_LOG_LEVEL_NONE, StringCast<ANSICHAR>(*Str).Get(), nullptr);
				Batch_ = NextBatch(&NewTokenId, 1);
				NOfDecode++;
			}
			
		}

		FString UEOp(Op.c_str());
		UE_LOG(LlamaCpp, Display, TEXT("%s"), *UEOp);
	}
}

void FllamaCppPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UnloadSmpl(Smpl_);
	UnloadCtx(Ctx_);
	UnloadModel(Model_);
	Smpl_ = nullptr;
	Ctx_ = nullptr;
	Model_ = nullptr;


	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LlamaCppHelperLibHandle_);
	LlamaCppHelperLibHandle_ = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FllamaCppPluginModule, llamaCppPlugin)
