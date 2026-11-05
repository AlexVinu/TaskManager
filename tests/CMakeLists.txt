cmake_minimum_required(VERSION 3.28)
project(tests_task_manager CXX)

include(FetchContent)

# Fetch googletest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_task_manager
        test_task_manager.cpp)

add_executable(test_task_group
        test_task_group.cpp)

add_executable(test_task_group_api
        test_task_group_api.cpp)

target_link_libraries(test_task_manager
    PRIVATE
    GTest::gtest_main
    task_manager       
)

target_link_libraries(test_task_group
    PRIVATE
    GTest::gtest_main
    task_manager       
)

target_link_libraries(test_task_group_api
    PRIVATE
    GTest::gtest_main
    task_manager       
)


include(GoogleTest)
gtest_discover_tests(test_task_manager)
gtest_discover_tests(test_task_group)
gtest_discover_tests(test_task_group_api)