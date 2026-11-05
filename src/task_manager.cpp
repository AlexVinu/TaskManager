#include "task_manager/internal/task_manager.h"

#include <oneapi/tbb.h>

struct tm_TaskManager::Impl 
{
    tbb::task_arena arena;
    Impl(uint8_t max_threads) : arena(max_threads) {}
    ~Impl()
    {
        arena.terminate();
    }
};

tm_TaskManager::tm_TaskManager(uint8_t max_threads) 
{
    p_Impl = std::make_unique<Impl>(max_threads);
}

tm_TaskManager::~tm_TaskManager() 
{
    
}

const uint8_t tm_TaskManager::GetMaxThreads() const
{
    return p_Impl->arena.max_concurrency();
}