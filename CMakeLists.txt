cmake_minimum_required(VERSION 3.20)
project(simple_thread_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include_directories(src)

add_executable(simple_thread_cpp
        src/main.cpp
        src/task.cpp
        src/task.h
        src/thread_factory.cpp
        src/thread_factory.h
        src/thread_pool.cpp
        src/thread_pool.h
        src/utils.cpp
        src/utils.h
        src/STL_thread.cpp
        src/STL_thread.h
        src/task_queue.h
        src/task_queue.cpp
        src/thread_manage.h
        src/thread_manage.cpp
)

target_link_libraries(simple_thread_cpp pthread)