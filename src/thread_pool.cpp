#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    simpleThread::ThreadPool::ThreadPool() {
        int size = cpuCount();
        ThreadPool(size, size);
    }

    ThreadPool::ThreadPool(int size) {
        ThreadPool(size, size);
    }

    // 构造函数, 并创建核心线程数, 线程数必须大于0
    ThreadPool::ThreadPool(int coreSize, int maxSize) : coreSize(coreSize), maxSize(maxSize) {
        if (this->coreSize <= 0) {
            this->coreSize = cpuCount();
        }
        if (this->maxSize <= 0 || this->maxSize < this->coreSize) {
            this->maxSize = this->coreSize;
        }

        for (int i = 0; i < this->coreSize; ++i) {
            this->createThread();
        }
    }

    void ThreadPool::execute(simpleThread::Runnable *runnable) const noexcept {
        Task* task = new Task;
        task->setType(taskType::runnable);
        task->setRunnable(runnable);
//        this->queue.push(task);
    }

    template<class T>
    std::future<T> ThreadPool::submit(simpleThread::Callable<T> &task) const noexcept {

    }

    void ThreadPool::shutdown() noexcept {}

    void ThreadPool::join() noexcept {}

    int ThreadPool::getCoreSize() const {
        return this->coreSize;
    }

    int ThreadPool::getActiveSize() const {
        return this->activateSiz;
    }
}