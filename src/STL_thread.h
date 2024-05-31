#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include "task_queue.h"
#include "process.h"

namespace simpleThread {
    class STLThread {
    private:
        std::thread work;
        TaskQueue *queue;
        Process process;
        std::atomic_int *counter = nullptr;

        // 创建线程
        void createThread();

    public:
        explicit STLThread(TaskQueue *);

        explicit STLThread(TaskQueue *, std::atomic_int *);

        auto getId();

        // 阻塞线程, 等待所有任务完成
        void join();

        // 关闭线程,未执行的任务丢弃
        void shutdown();

        // 分析线程, 设置为daemon模式
        void setDaemon();

        // 启动线程
        void start();
    };
}


#endif //SIMPLE_THREAD_CPP_STL_THREAD_H
