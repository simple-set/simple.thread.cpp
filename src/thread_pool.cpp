#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    ThreadPool::ThreadPool() : ThreadPool(cpuCount()) {}

    ThreadPool::ThreadPool(int size) : ThreadPool(size, size) {}

    // 构造函数, 并创建核心线程数, 线程数必须大于0
    ThreadPool::ThreadPool(int coreSize, int maxSize) : coreSize(coreSize), maxSize(maxSize) {
        if (this->coreSize <= 0) {
            this->coreSize = cpuCount();
        }
        if (this->maxSize <= 0 || this->maxSize < this->coreSize) {
            this->maxSize = this->coreSize;
        }
        this->initThread();
    }

    void ThreadPool::initThread() {
        for (int i = 0; i < this->coreSize; ++i) {
            this->makeThread();
        }
    }

    void ThreadPool::makeThread() {
        std::lock_guard<std::mutex> lock(this->mtx);
        this->threads.push_back(this->factory.create(&this->taskQueue, &this->activateSiz));
    }

    void ThreadPool::execute(Runnable *runnable) noexcept {
        Task *task = new Task(runnable);
        this->taskQueue.push(task);
    }

    template<class T>
    std::future<T> ThreadPool::submit(Callable<T> &task) const noexcept {}

    void ThreadPool::join() {
        for (const auto &thread: this->threads) {
            thread->join();
        }
    }

    void ThreadPool::shutdown() {
        for (const auto &thread: this->threads) {
            thread->shutdown();
        }
    }

    int ThreadPool::getCoreSize() const {
        return this->coreSize;
    }

    int ThreadPool::getActiveSize() const {
        return this->activateSiz;
    }
}