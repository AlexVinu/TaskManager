#include "task_manager/task_manager.h"

#include <oneapi/tbb.h>

namespace task_manager {
    struct TaskManager::Impl 
    {
        tbb::task_arena arena;
        Impl(uint8_t max_threads) : arena(max_threads) {}
        ~Impl()
        {
            arena.terminate();
        }
    };

    TaskManager::TaskManager(uint8_t max_threads) 
    {
        p_Impl = std::make_unique<Impl>(max_threads);
    }

    TaskManager::~TaskManager() 
    {
        
    }

    const uint8_t TaskManager::GetMaxThreads() const
    {
        return p_Impl->arena.max_concurrency();
    }
}