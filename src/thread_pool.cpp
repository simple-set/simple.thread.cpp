#include <cpuid.h>
#include "thread_pool.h"
#include "utils.h"

namespace simpleThread {
    ThreadPool::~ThreadPool() {
        int size = cpuCount();
        ThreadPool(size, size);
    }

    ThreadPool::ThreadPool(int size) {
        ThreadPool(size, size);
    }

    ThreadPool::ThreadPool(int coreSize, int maxSize) : coreSize(coreSize), maxSize(maxSize) {
        // createThread();
    }

    void ThreadPool::execute(simpleThread::Task &task) const noexcept {
        if (this->activateSize < this->maxSize) {
        }
    }

    template<class T>
    std::future<T> ThreadPool::submit(simpleThread::Callable<T> &task) const noexcept{

    }

    void ThreadPool::shutdown() noexcept {}

    void ThreadPool::join() noexcept {}

    int ThreadPool::getSize() const {
        return this->coreSize;
    }
}