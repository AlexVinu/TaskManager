#pragma once

#include "i_task_group.h"
#include "task.h"

#include <memory>
#include <type_traits>

namespace task_manager {
    class TaskGroup : ITaskGroup
    {
    public:
        TaskGroup();
        ~TaskGroup() override;
        
        template <typename CallbackFn, typename... DataType>
        void RunTask(CallbackFn&& callback, DataType&&... data)
        {
            auto task = new Task<std::decay_t<CallbackFn>, DataType...>(
                std::forward<CallbackFn>(callback), 
                std::forward<DataType>(data)...
            );
            RunITask(task);
        }

        void RunITask(ITask* task) override;
        void Wait() override;
    private:
        struct Impl;
        std::unique_ptr<Impl> p_Impl;
    };
}