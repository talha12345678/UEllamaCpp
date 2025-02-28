#if defined _WIN32 || defined _WIN64
#define DLLIMPORT __declspec(dllimport)
#elif defined __linux__
#define DLLIMPORT __attribute__((visibility("default")))
#else
#define DLLIMPORT
#endif

#include "llamaCpp/Include/llama.h"
#include <string>
#include <vector>

DLLIMPORT void ExampleLibraryFunction();
DLLIMPORT void LoadBackend();
DLLIMPORT llama_model* LoadModel(int InNgl, const char* InModelPath);
DLLIMPORT const llama_vocab* GetModelVocab(llama_model* InModel);
DLLIMPORT int32_t TokenizePrompt(const llama_vocab* InVocab, const char* InPrompt, llama_token* OutTokens, int32_t InMaxTokens);
DLLIMPORT int32_t TokenizePromptEx(const char* InPrompt, const llama_vocab* InVocab, llama_model* InModel, llama_token* OutTokens);
DLLIMPORT bool InitializeContext(int InNPrompt, int InNPredict, llama_model* InModel, llama_context* OutCtx);
DLLIMPORT int32_t PrintPromptByToken(const llama_vocab* InVocab, llama_token InToken, char* InBuff);
DLLIMPORT void UnloadModel(llama_model* InModel);
