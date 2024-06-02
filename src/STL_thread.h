#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include <ctime>
#include <functional>
#include "task_queue.h"

namespace simpleThread {
    class STLThread {
    private:
        // 任务线程
        std::thread workThread;

        // 任务队列
        TaskQueue *queue;

        // 核心线程数
        int const *coreSize = nullptr;

        // 最大线程数
        int const *maxSize = nullptr;

        // 活跃线程数
        int const *activateSiz = nullptr;

        // 任务队列为空时, 退出执行
        bool volatile done = false;

        // 不管队列状态，立即退出执行
        bool volatile exit = false;

        // 任务轮训间隔时间(毫秒)
        int const WAIT_TIME = 50;

        // 空闲退出时间(秒)
        int const IDLE_EXIT_TIME = 60;

        // 线程最近执行时间戳
        long executeTime = std::time(nullptr);

        // 线程空闲时间
        bool freeTime() const;

        // 线程等待超时
        bool waitTimeout() const;

        // 从管理器中移出线程
        std::function<void(STLThread *)> removeThread;

        // 启动线程
        void start();

        // 执行任务
        void execute();

        // 执行业务
        static void work(Task *task) noexcept;

    public:
        explicit STLThread(TaskQueue *);

        std::thread::id getId();

        // 阻塞线程, 等待所有任务完成
        void join();

        // 关闭线程, 丢弃未执行的任务
        void shutdown();

        // 分析线程, 设置为daemon模式
        void setDaemon();

        void setRemoveThread(const std::function<void(STLThread *)> &function);

        void setCoreSize(const int *coreSize);

        void setMaxSize(const int *maxSize);

        void setActivateSiz(const int *activateSiz);
    };
}

#endif //SIMPLE_THREAD_CPP_STL_THREAD_H

#pragma clang diagnostic pop