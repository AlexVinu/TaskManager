#include "task_manager/internal/task.h"
#include "task_manager/api/core.h"

tm_Task::tm_Task(tm_execute_callback exec_fn, tm_destroy_callback destroy_fn, void* ctx)
    : m_ExecuteCallback(exec_fn), m_DestroyCallback(destroy_fn), m_Ctx(ctx)
{
}

tm_Task::~tm_Task()
{
    Destroy();
}

void tm_Task::Execute()
{
    if(m_ExecuteCallback)
        m_ExecuteCallback(m_Ctx);
}

void tm_Task::Destroy()
{
    m_ExecuteCallback = nullptr;
    if(m_DestroyCallback)
        m_DestroyCallback(m_Ctx);
    m_DestroyCallback = nullptr;
}