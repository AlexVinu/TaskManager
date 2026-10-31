#pragma once

#include "i_task.h"
#include <tuple>

namespace task_manager {

    template <typename CallbackFn, typename... DataType>
    struct Task: public ITask
    {
        template <typename F, typename... Args>
        Task(F&& callback, Args&&... args)
            : callback(std::forward<F>(callback)),
            data(std::forward<Args>(args)...) {}
        
        void Execute() noexcept override 
        {
            if (callback) 
            {
                std::apply(callback, data);
            }
        }
        void Destroy() noexcept override
        {
            delete this;
        }
    protected:
        ~Task() noexcept override = default;

        CallbackFn callback;
        std::tuple<DataType...> data;
    };
}