#if defined _WIN32 || defined _WIN64
    #include <Windows.h>

    #define DLLEXPORT __declspec(dllexport)
#else
    #include <stdio.h>
#endif

#include "llamaCpp/Include/llama.h"
#include <string>
#include <vector>

#ifndef DLLEXPORT
    #define DLLEXPORT
#endif

DLLEXPORT void ExampleLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
	MessageBox(NULL, TEXT("Hello world!"), NULL, MB_OK);
#else
    printf("Hello World");
#endif
    
}

//enum class BackEnds { all, cuda, hip, cpu };
DLLEXPORT void LoadBackend()
{
    ggml_backend_load_all();    
}


DLLEXPORT llama_model* LoadModel(int InNgl, const char* InModelPath)
{
    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = InNgl;    
    llama_model* OutModel = (InModelPath) ? llama_model_load_from_file(InModelPath, model_params) : nullptr;

    return OutModel;    
}

DLLEXPORT const llama_vocab* GetModelVocab(llama_model* InModel)
{
    const llama_vocab* vocab = (InModel) ? llama_model_get_vocab(InModel) : nullptr;
    return vocab;
}

DLLEXPORT int32_t TokenizePrompt(const llama_vocab* InVocab, const char* InPrompt, llama_token* OutTokens, int32_t InMaxTokens)
{
    return (InPrompt && InVocab) ? llama_tokenize(InVocab, InPrompt, static_cast<int32_t>(strlen(InPrompt)), OutTokens, InMaxTokens, true, true) : -1;
}

DLLEXPORT int32_t TokenizePromptEx(const char* InPrompt, const llama_vocab* InVocab, llama_model* InModel, llama_token* OutTokens)
{
    int32_t NoOfTokens = 0;
    if (InPrompt && InModel && InVocab)
    {
        const int n_prompt = -llama_tokenize(InVocab, InPrompt, static_cast<int32_t>(strlen(InPrompt)), NULL, 0, true, true);
        OutTokens = new llama_token[n_prompt]();
        NoOfTokens = llama_tokenize(InVocab, InPrompt, static_cast<int32_t>(strlen(InPrompt)), OutTokens, n_prompt, true, true);
    }    
    return NoOfTokens;
}

DLLEXPORT bool InitializeContext(int InNPrompt, int InNPredict, llama_model* InModel, llama_context* OutCtx)
{
    if(InModel && !OutCtx)
    {
        llama_context_params ctx_params = llama_context_default_params();
        // n_ctx is the context size
        ctx_params.n_ctx = InNPrompt + InNPredict - 1;
        // n_batch is the maximum number of tokens that can be processed in a single call to llama_decode
        ctx_params.n_batch = InNPrompt;
        // enable performance counters
        ctx_params.no_perf = false;

        OutCtx = llama_init_from_model(InModel, ctx_params);

        return (OutCtx != nullptr);
    }
    else
    {
        return false;
    }    
}

DLLEXPORT int32_t PrintPromptByToken(const llama_vocab* InVocab, llama_token InToken, char *InBuff)
{
    return (InVocab && InBuff) ? llama_token_to_piece(InVocab, InToken, InBuff, sizeof(InBuff), 0, true) : -1;
}

DLLEXPORT void UnloadModel(llama_model* InModel)
{
    llama_model_free(InModel);
}