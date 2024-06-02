#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef SIMPLE_THREAD_CPP_THREAD_POOL_H
#define SIMPLE_THREAD_CPP_THREAD_POOL_H

#include <future>
#include <vector>
#include "task.h"
#include "thread_factory.h"
#include "task_queue.h"
#include "thread_manage.h"

namespace simpleThread {
    class ThreadPool {
    private:
        // 线程管理器
        ThreadManage threadManage;

        // 任务队列
        TaskQueue taskQueue;

        // 执行任务预处理
        bool perExecute();

    public:
        ThreadPool();

        explicit ThreadPool(int size);

        explicit ThreadPool(int coreSize, int maxSize);

        // 提交任务
        void execute(simpleThread::Runnable *) noexcept;

        void execute(const std::function<void()> &) noexcept;

        // 提交任务, 可异步获取结果
        template<class T>
        std::future<T> submit() const noexcept;

        // 阻塞线程池, 等待所有任务完成
        void join();

        // 关闭线程池, 丢弃未执行的任务
        void shutdown();

        // 核心线程数
        int getCoreSize() const;

        //最大线程数
        int getMaxSize() const;

        // 活跃线程数
        int getActiveSize() const;
    };
}

#endif //SIMPLE_THREAD_CPP_THREAD_POOL_H

#pragma clang diagnostic pop