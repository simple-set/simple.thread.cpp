#ifndef SIMPLE_THREAD_CPP_PROCESS_H
#define SIMPLE_THREAD_CPP_PROCESS_H

#include <thread>
#include <mutex>
#include "task.h"
#include "task_queue.h"

namespace simpleThread {
    class Process {
    private:
        TaskQueue *queue;
        std::timed_mutex *mtx;
        // 线程状态
        bool done = false;
        // 线程监听任务队列轮询时间(毫秒)
        int const POLL_TIME = 50;

        Task *getTask() const noexcept; // NOLINT(*-use-nodiscard)

    public:
        explicit Process(TaskQueue *queue);

        void work() const noexcept;

        void setDone();

        void static doWork(Task *task) noexcept;
    };
}


#endif //SIMPLE_THREAD_CPP_PROCESS_H
