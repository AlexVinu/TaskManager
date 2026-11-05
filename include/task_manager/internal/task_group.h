#pragma once

#include "task.h"
#include "task_manager/api/core.h"

#include "task_manager/api/task_desc.h"
#include "task_manager/api/task_group_api.h"

#include <memory>
#include <tuple>
#include <utility>

extern "C" const tm_TaskGroupApi* CALL tm_GetTaskGroupApi();

class tm_TaskGroup
{
public:
    tm_TaskGroup();
    ~tm_TaskGroup();
    
    template<typename... Data>
    void RunTask(tm_execute_callback&& callback, Data&&... data)
    {
        using DataTuple = std::tuple<Data&&...>;
        auto data_ = new DataTuple(std::forward<Data&&>(data)...);
        tm_destroy_callback des_cal = [](void* ctx)
        {
            auto context = static_cast<DataTuple*>(ctx);
            delete context;
        };
        auto task = new tm_Task(callback, des_cal, data_);
        RunTask(task);
    }

    void RunTask(tm_Task* task);
    void RunTask(tm_TaskDescriptor* desc);
    void Wait();
private:
    struct Impl;
    std::unique_ptr<Impl> p_Impl;
};