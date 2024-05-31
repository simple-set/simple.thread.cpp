#ifndef SIMPLE_THREAD_CPP_PROCESS_H
#define SIMPLE_THREAD_CPP_PROCESS_H

#include <thread>
#include <mutex>
#include "task.h"
#include "task_queue.h"

namespace simpleThread {
    class Process {
    private:
        // 任务队列
        TaskQueue *queue;

        // 任务队列为空时, 退出执行
        bool volatile done = false;

        // 不管队列状态，立即退出执行
        bool volatile shutdown = false;

        // 任务轮训间隔时间(毫秒)
        int const WAIT_TIME = 50;

        Task *getTask() const noexcept; // NOLINT(*-use-nodiscard)

    public:
        void setDone();

        void setShutdown();

        void setQueue(TaskQueue *taskQueue);

        void work() const noexcept;

        void static executeTask(Task *task) noexcept;
    };
}


#endif //SIMPLE_THREAD_CPP_PROCESS_H
