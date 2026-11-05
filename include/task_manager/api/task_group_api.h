#pragma once

#include "task_desc.h"
#include <cstdint>
#include <tuple>

struct tm_TaskGroup;

struct tm_TaskGroupApi
{
    uint32_t struct_size;

    void (CALL *run_task)(tm_TaskDescriptor* desc, tm_TaskGroup* task_group);
    void (CALL *wait)(tm_TaskGroup* task_group);
};

template<typename... Data>
void tm_RunTask(const tm_TaskGroupApi* task_group_api,
    tm_TaskGroup* task_group, 
    tm_execute_callback&& callback, 
    Data&&... data)
{
    using DataTuple = std::tuple<Data&&...>;
    auto data_ = new DataTuple(std::forward<Data&&>(data)...);
    tm_destroy_callback des_cal = [](void* ctx)
    {
        auto context = static_cast<DataTuple*>(ctx);
        delete context;
    };
    auto task_desc = new tm_TaskDescriptor(callback, des_cal, data_);
    task_group_api->run_task(task_desc, task_group);
}

inline void tm_Wait(const tm_TaskGroupApi* task_group_api, tm_TaskGroup* task_group)
{
    task_group_api->wait(task_group);
}