// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "llamaCppPluginLibrary/LlamaCppHelperLib.h"

class FllamaCppPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void LoadLLMModel(const FString& InModelPath, const int32 InNgl);

private:
	/** Handle to the test dll we will load */
	void*	LlamaCppHelperLibHandle;
	llama_model* Model;
};
