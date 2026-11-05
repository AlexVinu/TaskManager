#pragma once

#if defined(_WIN32)
    #define CALL __cdecl
#else
    #define CALL
#endif

typedef void(*tm_execute_callback)(void*);
typedef void(*tm_destroy_callback)(void*);