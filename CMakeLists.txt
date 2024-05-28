cmake_minimum_required(VERSION 3.28)
project(simple_thread_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(simple_thread_cpp
        src/main.cpp
        src/main.h
        src/task.cpp
        src/task.h
        src/thread.cpp
        src/thread.h
        src/thread_factory.cpp
        src/thread_factory.h
        src/thread_manage.cpp
        src/thread_manage.h
        src/thread_pool.cpp
        src/thread_pool.h)
