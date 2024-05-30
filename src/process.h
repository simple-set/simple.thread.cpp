#ifndef SIMPLE_THREAD_CPP_PROCESS_H
#define SIMPLE_THREAD_CPP_PROCESS_H

#include "task.h"
#include <thread>
#include "task_queue.h"

namespace simpleThread {
    class process {
    private:
        TaskQueue *queue;
        std::mutex *mtx;

        Task *getTask() noexcept;

    public:
        [[noreturn]] void work() const noexcept;

        void done() noexcept;
    };
}


#endif //SIMPLE_THREAD_CPP_PROCESS_H
