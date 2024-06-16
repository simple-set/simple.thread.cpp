#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    ThreadPool::ThreadPool() : ThreadPool(cpuCount()) {}

    ThreadPool::ThreadPool(int size) : ThreadPool(size, size) {}

    // 构造函数, 并创建核心线程数, 线程数必须大于0
    ThreadPool::ThreadPool(int coreSize, int maxSize) : threadManage(coreSize, maxSize, &taskQueue) {
        if (coreSize <= 0) {
            this->threadManage.setCoreSize(cpuCount());
        }
        if (maxSize <= 0 || maxSize < coreSize) {
            this->threadManage.setMaxSize(cpuCount());
        }
        this->threadManage.initThreads();
    }

    bool ThreadPool::canExecute() {
        if (this->threadManage.getClose() || this->taskQueue.getClose()) {
            // 线程池已关闭,丢弃任务
            return false;
        }
        if (this->threadManage.getActivateSiz() < this->threadManage.getMaxSize()) {
            this->threadManage.addThread();
        }
        return true;
    }

    void ThreadPool::join() {
        this->taskQueue.setClose();
        this->threadManage.join();
    }

    void ThreadPool::shutdown() {
        this->taskQueue.setClose();
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