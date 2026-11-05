#pragma once

#include "task_group.h"
#include <memory>

class tm_TaskManager 
{
public:
    tm_TaskManager(uint8_t max_threads = 0);
    ~tm_TaskManager();
    const uint8_t GetMaxThreads() const;
private:
    struct Impl;
    std::unique_ptr<Impl> p_Impl;
};