#include <gtest/gtest.h>
#include "task_manager/task_manager.h"

using namespace task_manager;

TEST(TaskManagerTest, CreateTaskManager) 
{
    TaskManager taskManager;
    ASSERT_GT(taskManager.GetMaxThreads(), 0);
};
