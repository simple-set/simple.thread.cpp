#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    ThreadPool::ThreadPool() {
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
        this->createThread();
        // for (int i = 0; i < this->coreSize; ++i) {
        //     this->createThread();
        // }
    }

    void ThreadPool::execute(Runnable *runnable) const noexcept {
        Task* task = new Task;
        task->setType(taskKind::runnable);
        task->setRunnable(runnable);
        // this->taskQueue.push(task);
    }

    template<class T>
    std::future<T> ThreadPool::submit(Callable<T> &task) const noexcept {

    }

    void ThreadPool::shutdown() noexcept {}

    void ThreadPool::join() noexcept {}

    int ThreadPool::getCoreSize() const {
        return this->coreSize;
    }

    int ThreadPool::getActiveSize() const {
        return this->activateSiz;
    }

    void ThreadPool::createThread() {
        for (int i = 0; i < this->coreSize; ++i) {
            // auto process = new Process(&this->taskQueue);

            // this->threads.emplace_back();
        }
    }
}