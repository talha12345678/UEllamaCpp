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

DLLEXPORT llama_context* InitializeContext(int InNPrompt, int InNPredict, llama_model* InModel)
{

    if(InModel)
    {
        llama_context_params ctx_params = llama_context_default_params();
        // n_ctx is the context size
        ctx_params.n_ctx = InNPrompt + InNPredict - 1;
        // n_batch is the maximum number of tokens that can be processed in a single call to llama_decode
        ctx_params.n_batch = InNPrompt;
        // enable performance counters
        ctx_params.no_perf = false;

        return llama_init_from_model(InModel, ctx_params);        
    }
    else
    {
        return nullptr;
    }    
}

DLLEXPORT llama_sampler* InitializeSampler(bool InMeasurePerformance)
{
    auto sparams = llama_sampler_chain_default_params();
    sparams.no_perf = InMeasurePerformance;
    llama_sampler* smpl = llama_sampler_chain_init(sparams);
    llama_sampler_chain_add(smpl, llama_sampler_init_greedy());
    return smpl;
}
DLLEXPORT llama_batch InitializeBatch(llama_token* InTokens, int32_t InNTokens)
{
    llama_batch batch;
    batch = (InTokens) ? llama_batch_get_one(InTokens, InNTokens) : batch;
    return batch;
} 

DLLEXPORT int32_t Decode(llama_context* InCtx, llama_batch InBatch)
{
    return llama_decode(InCtx, InBatch);
}

DLLEXPORT llama_token Sample(llama_sampler* InSmpl, llama_context* InCtx, int32_t InIndex)
{
    return llama_sampler_sample(InSmpl, InCtx, InIndex);
}

DLLEXPORT bool IsEog(const llama_vocab* InVocab, llama_token InToken)
{
    return llama_vocab_is_eog(InVocab, InToken);
}

DLLEXPORT uint32_t GetCtxSize(llama_context* InCtx)
{
    return llama_n_ctx(InCtx);    
}

DLLEXPORT int32_t GetCtxSizeUsed(llama_context* InCtx)
{
    return llama_get_kv_cache_used_cells(InCtx);
}

DLLEXPORT int32_t PrintPromptByToken(const llama_vocab* InVocab, llama_token InToken, char *OutBuff)
{
    return (InVocab && OutBuff) ? llama_token_to_piece(InVocab, InToken, OutBuff, sizeof(OutBuff), 0, true) : -1;
}

DLLEXPORT void LogSet(ggml_log_callback InCallback, void* InUserData)
{
    llama_log_set(InCallback, InUserData);
}

DLLEXPORT void UnloadSmpl(llama_sampler* InSmpl)
{
    llama_sampler_free(InSmpl);
    //llama_print_system_info()
    //llama_log_set()
}

DLLEXPORT void UnloadCtx(llama_context* InCtx)
{
    llama_free(InCtx);    
}

DLLEXPORT void UnloadModel(llama_model* InModel)
{
    llama_model_free(InModel);
}