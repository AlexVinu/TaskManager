#pragma once

#include "task_group.h"
#include <memory>

namespace task_manager {

    class TaskManager 
    {
    public:
        TaskManager(uint8_t max_threads = 0);
        ~TaskManager();
        const uint8_t GetMaxThreads() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> p_Impl;
    };
}