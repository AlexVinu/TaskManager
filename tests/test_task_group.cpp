#include <gtest/gtest.h>
#include "task_manager/task_manager.h"

using namespace task_manager;

struct TaskGroupFixture: public testing::Test 
{
    TaskManager taskManager;
};

TEST_F(TaskGroupFixture, RunTaskAndWait) 
{
    TaskGroup taskGroup;

    bool taskExecuted = false;

    taskGroup.RunTask([](bool& flag){flag = true;}, taskExecuted);
    taskGroup.Wait();

    ASSERT_TRUE(taskExecuted);

    int num = 0;
    taskGroup.RunTask([](int& n){n = 42;}, num);
    taskGroup.Wait();
    ASSERT_EQ(num, 42);
}
