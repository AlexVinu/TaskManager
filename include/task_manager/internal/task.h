#pragma once

#include "task_manager/api/core.h"

class tm_Task
{
public:
    tm_Task(tm_execute_callback exec_fn, tm_destroy_callback destroy_fn, void*);
    tm_Task(const tm_Task&) = delete;
    ~tm_Task();
    void Execute();
    void Destroy();
private:
    tm_execute_callback m_ExecuteCallback;
    tm_destroy_callback m_DestroyCallback;
    void* m_Ctx;
};