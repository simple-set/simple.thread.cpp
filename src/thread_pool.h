#ifndef SIMPLE_THREAD_CPP_THREAD_POOL_H
#define SIMPLE_THREAD_CPP_THREAD_POOL_H

#include <future>
#include "task.h"
#include "thread_factory.h"
#include "task_queue.h"

namespace simpleThread {
    class ThreadPool {
    private:
        int coreSize;
        int maxSize;
        int activateSiz;
        TaskQueue taskQueue;
        simpleThread::ThreadFactory factory;

        void createThread() {
            this->factory.create();
        }

    public:
        ThreadPool();

        ThreadPool(int size);

        ThreadPool(int coreSize, int maxSize);

        // 析构函数
        virtual ~ThreadPool() = default;

        // 提交任务
        void execute(simpleThread::Runnable *runnable) const noexcept;

        // 提交任务, 可异步获取结果
        template<class T>
        std::future<T> submit(simpleThread::Callable<T> &task) const noexcept;

        // 关闭线程池,会等待所有任务执行完成
        void shutdown() noexcept;

        // 立即关闭线程池,未执行的任务被丢弃
        void shutdownNow() noexcept;

        // 等待线程结束, 在shutdown之后调用, 否则将永久等待
        void join() noexcept;

        // 返回核心线程数
        int getCoreSize() const;

        // 活跃线程数
        int getActiveSize() const;
    };
}

#endif //SIMPLE_THREAD_CPP_THREAD_POOL_H
