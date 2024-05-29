cmake_minimum_required(VERSION 3.28)
project(simple_thread_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

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
        src/handler.cpp
        src/handler.h
        src/thread.cpp
        src/thread.h
)
