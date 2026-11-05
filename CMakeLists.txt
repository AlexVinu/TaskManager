cmake_minimum_required(VERSION 3.28)

project(task_manager LANGUAGES CXX)

enable_testing()

# Cpp standart
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TESTING "Build unit tests" ON)

find_package(TBB REQUIRED)

# Target
add_library(task_manager)

# Connection modules and headers
target_sources(task_manager
    PRIVATE
        src/task_manager.cpp
        src/task_group.cpp
        src/task.cpp

    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/task_manager/api/core.h
            include/task_manager/api/task_desc.h

            include/task_manager/internal/task_manager.h
            include/task_manager/internal/task_group.h
            include/task_manager/internal/task.h
)

target_include_directories(task_manager
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/utils"
)

# Linking externals
target_link_libraries(task_manager
    PRIVATE
        TBB::tbb)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()