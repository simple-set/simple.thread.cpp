//
// Created by xk on 2024/5/28.
//

#ifndef SIMPLE_THREAD_CPP_THREAD_POOL_H
#define SIMPLE_THREAD_CPP_THREAD_POOL_H


#include <future>
#include "task.h"

namespace simpleThread {
    class ThreadPool {
    private:
        int coreSize;
        int maxSize;
        int activateSize;

        void createThread() noexcept;

    public:
        ThreadPool();

        ThreadPool(int size);

        ThreadPool(int coreSize, int maxSize);

        // 析构函数
        virtual ~ThreadPool();

        // 提交任务
        void execute(simpleThread::Task &task) const noexcept;

        // 提交任务, 可异步获取结果
        template<class T>
        std::future<T> submit(simpleThread::Callable<T> &task) const noexcept;

        // 关闭线程池,会等待所有任务执行完成
        void shutdown() noexcept;

        // 立即关闭线程池,未执行的任务被丢弃
        void shutdownNow() noexcept;

        // 等待线程结束, 在shutdown之后调用
        void join() noexcept;

        // 返回核心线程数
        int getSize() const;

        // 活跃线程数
        int activeSize() const;
    };
}


#endif //SIMPLE_THREAD_CPP_THREAD_POOL_H
