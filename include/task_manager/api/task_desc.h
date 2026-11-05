#pragma once

#include "core.h"

struct tm_TaskDescriptor
{
    tm_execute_callback execute_callback;
    tm_destroy_callback destroy_callback;
    void* ctx;
};