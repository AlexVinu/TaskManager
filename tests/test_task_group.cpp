#include <gtest/gtest.h>
#include <tuple>
#include "task_manager/internal/task_manager.h"

struct TaskGroupFixture: public testing::Test 
{
    tm_TaskManager taskManager;
};

TEST_F(TaskGroupFixture, RunTaskAndWait) 
{
    tm_TaskGroup taskGroup;

    bool taskExecuted = false;
    int num = 0;

    taskGroup.RunTask([](void* ctx){
        auto context = static_cast<std::tuple<bool&, int&>*>(ctx);
        std::get<0>(*context) = true;
        std::get<1>(*context) = 42;
    }, taskExecuted, num);
    taskGroup.Wait();

    ASSERT_TRUE(taskExecuted);
    ASSERT_EQ(num, 42);
}
