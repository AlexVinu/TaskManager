#include "task_manager/internal/task_group.h"
#include "task_manager/api/task_group_api.h"
#include "task_manager/internal/task.h"

#include <oneapi/tbb.h>
#include <vector>


struct tm_TaskGroup::Impl 
{
    tbb::task_group task_group;
    std::vector<std::unique_ptr<tm_Task>> tasks;
};

tm_TaskGroup::tm_TaskGroup() 
{
    p_Impl = std::make_unique<Impl>();
}

tm_TaskGroup::~tm_TaskGroup() 
{
    Wait();
}

void tm_TaskGroup::RunTask(tm_Task* task) 
{
    p_Impl->task_group.run([task]() {
        task->Execute();
    });
    p_Impl->tasks.emplace_back(task);
}

void tm_TaskGroup::RunTask(tm_TaskDescriptor* desc)
{
    auto task = new tm_Task(desc->execute_callback, desc->destroy_callback, desc->ctx);
    RunTask(task);
}

void tm_TaskGroup::Wait() 
{
    p_Impl->task_group.wait();
    p_Impl->tasks.clear();
}

void CALL RunTask(tm_TaskDescriptor* desc, tm_TaskGroup* task_group)
{
    task_group->RunTask(desc);
}

void CALL Wait(tm_TaskGroup* task_group)
{
    task_group->Wait();
}

static const tm_TaskGroupApi task_group_api = 
{
    sizeof(tm_TaskGroupApi),
    &RunTask,
    &Wait
};

extern "C" const tm_TaskGroupApi* CALL tm_GetTaskGroupApi()
{
    return &task_group_api;
}