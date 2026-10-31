#pragma once

namespace task_manager {
    struct ITask
    {
        virtual void Execute() noexcept = 0;
        virtual void Destroy() noexcept = 0;
    protected:
        virtual ~ITask() noexcept = default;
    };
}
