#pragma once

#include "i_task.h"

namespace task_manager {
    struct ITaskGroup 
    {
        virtual ~ITaskGroup() = default;
        virtual void RunITask(ITask* task) = 0;
        virtual void Wait() = 0;
    };
}