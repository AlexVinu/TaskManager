#include <gtest/gtest.h>
#include "task_manager/task_manager.h"

using namespace task_manager;

struct ITaskGroupFixture: public testing::Test 
{
    TaskManager taskManager;
};

TEST_F(ITaskGroupFixture, RunTaskAndWait) 
{
    ITaskGroup* taskGroup = CreateTaskGroup();

    bool taskExecuted = false;
    int num = 0;

    RunTask(taskGroup, [](bool& flag, int& n){flag = true; n = 42;}, taskExecuted, num);
    taskGroup->Wait();

    ASSERT_TRUE(taskExecuted);
    ASSERT_EQ(num, 42);

    DestroyTaskGroup(taskGroup);
}
