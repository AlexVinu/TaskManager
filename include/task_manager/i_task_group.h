#pragma once

#include "task.h"

namespace task_manager {
    struct ITaskGroup 
    {
        virtual ~ITaskGroup() = default;
        virtual void RunITask(ITask* task) = 0;
        virtual void Wait() = 0;
    };

    template <typename CallbackFn, typename... DataType>
    void RunTask(ITaskGroup* taskGroup, CallbackFn&& callback, DataType&&... data)
    {
        auto task = new Task<std::decay_t<CallbackFn>, DataType...>(
            std::forward<CallbackFn>(callback), 
            std::forward<DataType>(data)...
        );
        taskGroup->RunITask(task);
    }

    extern "C" ITaskGroup* CreateTaskGroup();
    extern "C" void DestroyTaskGroup(ITaskGroup* taskGroup);
}