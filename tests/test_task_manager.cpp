#include <gtest/gtest.h>
#include "task_manager/internal/task_manager.h"

TEST(TaskManagerTest, CreateTaskManager) 
{
    tm_TaskManager taskManager;
    ASSERT_GT(taskManager.GetMaxThreads(), 0);
};
