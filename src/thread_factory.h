#ifndef SIMPLE_THREAD_CPP_THREAD_FACTORY_H
#define SIMPLE_THREAD_CPP_THREAD_FACTORY_H

#include <thread>
#include <mutex>
#include "task_queue.h"
#include "STL_thread.h"

namespace simpleThread {
    class ThreadFactory {
    private:
        std::mutex mtx;
    public:
        STLThread *create(TaskQueue *queue, std::atomic_int *counter) noexcept;
    };
}

#endif //SIMPLE_THREAD_CPP_THREAD_FACTORY_H
