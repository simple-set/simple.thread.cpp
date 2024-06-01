#ifndef SIMPLE_THREAD_CPP_THREAD_POOL_H
#define SIMPLE_THREAD_CPP_THREAD_POOL_H

#include <future>
#include <vector>
#include "task.h"
#include "thread_factory.h"
#include "task_queue.h"
#include "process.h"

namespace simpleThread {
    class ThreadPool {
    private:
        // 核心线程数
        int coreSize = 0;
        // 最大线程数
        int maxSize = 0;
        // 活跃线程数
        std::atomic_int activateSiz = 0;
        // 创建线程锁, 创建线程时不可并发
        std::mutex mtx;
        // 工作线程
        std::vector<STLThread *> threads;
        // 任务队列
        TaskQueue taskQueue;
        // 线程工厂
        simpleThread::ThreadFactory factory;

        // 初始化线程池
        void initThread();

        // 创建线程对象
        void makeThread();

    public:
        ThreadPool();

        explicit ThreadPool(int size);

        explicit ThreadPool(int coreSize, int maxSize);

        // 析构函数
        virtual ~ThreadPool() = default;

        // 提交任务
        void execute(simpleThread::Runnable *runnable) noexcept;

        // 提交任务, 可异步获取结果
        template<class T>
        std::future<T> submit(simpleThread::Callable<T> &task) const noexcept;

        // 阻塞线程池, 等待所有任务完成
        void join();

        // 关闭线程池, 丢弃未执行的任务
        void shutdown();

        // 返回核心线程数
        int getCoreSize() const;

        // 活跃线程数
        int getActiveSize() const;
    };
}

#endif //SIMPLE_THREAD_CPP_THREAD_POOL_H
