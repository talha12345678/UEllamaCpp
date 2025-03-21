// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "llamaCppPluginLibrary/LlamaCppHelperLib.h"

//DECLARE_LOG_CATEGORY_EXTERN(LlamaCpp, Log, All);
DECLARE_LOG_CATEGORY_CLASS(LlamaCpp, Log, All);

class FllamaCppPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void LoadLLMModel(const FString& InModelPath, const int32 InNgl, const FString& InPrompt);

private:
	/** Handle to the test dll we will load */
	void*	LlamaCppHelperLibHandle_;
	llama_model* Model_;
	llama_context* Ctx_;
	llama_sampler* Smpl_;
	llama_batch Batch_;
};
