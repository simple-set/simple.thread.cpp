#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    ThreadPool::ThreadPool() : ThreadPool(cpuCount()) {}

    ThreadPool::ThreadPool(int size) : ThreadPool(size, size) {}

    // 构造函数, 并创建核心线程数, 线程数必须大于0
    ThreadPool::ThreadPool(int coreSize, int maxSize): threadManage(coreSize, maxSize, &taskQueue) {
        if (coreSize <= 0) {
            this->threadManage.setCoreSize(coreSize);
        }
        if (maxSize <= 0 || maxSize < coreSize) {
            this->threadManage.setMaxSize(maxSize);
        }
        this->threadManage.initThreads();
    }

    void ThreadPool::execute(Runnable *runnable) noexcept {
        if (this->threadManage.getClose()) {
            // 线程池已关闭,丢弃任务
            return;
        }
        Task *task = new Task(runnable);
        this->taskQueue.push(task);
    }

    template<class T>
    std::future<T> ThreadPool::submit() const noexcept {}

    void ThreadPool::join() {
        this->threadManage.join();
    }

    void ThreadPool::shutdown() {
        this->threadManage.shutdown();
    }

    int ThreadPool::getCoreSize() const {
        return this->threadManage.getCoreSize();
    }

    int ThreadPool::getActiveSize() const {
        return this->threadManage.getActivateSiz();
    }

    int ThreadPool::getMaxSize() const {
        return this->threadManage.getMaxSize();
    }
}