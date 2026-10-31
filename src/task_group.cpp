#include "task_manager/task_group.h"

#include <oneapi/tbb.h>
#include <vector>

namespace task_manager {

    auto ITaskDeleter = [](ITask* task) { task->Destroy(); };

    struct TaskGroup::Impl 
    {
        tbb::task_group taskGroup;
        std::vector<std::unique_ptr<ITask, decltype(ITaskDeleter)>> tasks;
    };

    TaskGroup::TaskGroup() 
    {
        p_Impl = std::make_unique<Impl>();
    }

    TaskGroup::~TaskGroup() 
    {
        p_Impl->taskGroup.wait();
    }

    void TaskGroup::RunITask(ITask* task) 
    {
        p_Impl->taskGroup.run([task]() {
            task->Execute();
        });
        p_Impl->tasks.emplace_back(task);
    }

    void TaskGroup::Wait() 
    {
        p_Impl->taskGroup.wait();
        p_Impl->tasks.clear();
    }

}