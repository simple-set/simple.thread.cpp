#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include <atomic>
#include <functional>
#include "task_queue.h"
#include "process.h"

namespace simpleThread {
    class STLThread {
    private:
        // 任务线程
        std::thread workThread;
        // 任务队列
        TaskQueue *queue;
        // 任务对象
        Process process;
        // 线程计数器
        std::atomic_int *counter = nullptr;

        // 启动线程
        void start();

        // 执行任务
        void execute();

    public:
        explicit STLThread(TaskQueue *);

        explicit STLThread(TaskQueue *, std::atomic_int *);

        auto getId();

        // 阻塞线程, 等待所有任务完成
        void join();

        // 关闭线程, 丢弃未执行的任务
        void shutdown();

        // 分析线程, 设置为daemon模式
        void setDaemon();
    };
}


#endif //SIMPLE_THREAD_CPP_STL_THREAD_H
