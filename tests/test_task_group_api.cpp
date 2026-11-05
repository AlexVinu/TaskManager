#include <gtest/gtest.h>
#include <tuple>
#include "task_manager/api/task_group_api.h"
#include "task_manager/internal/task_manager.h"

struct TaskGroupApiFixture: public testing::Test 
{
    tm_TaskManager taskManager;
};

TEST_F(TaskGroupApiFixture, RunTaskAndWait) 
{
    tm_TaskGroup taskGroup;

    bool taskExecuted = false;
    int num = 0;

    auto task_group_api = tm_GetTaskGroupApi();

    tm_RunTask(task_group_api, &taskGroup, [](void* ctx){
        auto context = static_cast<std::tuple<bool&, int&>*>(ctx);
        std::get<0>(*context) = true;
        std::get<1>(*context) = 42;
    }, taskExecuted, num);

    tm_Wait(task_group_api, &taskGroup);

    ASSERT_TRUE(taskExecuted);
    ASSERT_EQ(num, 42);
}
