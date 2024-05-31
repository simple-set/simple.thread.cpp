#ifndef SIMPLE_THREAD_CPP_TASK_QUEUE_H
#define SIMPLE_THREAD_CPP_TASK_QUEUE_H

#include <deque>
#include <mutex>
#include "task.h"

namespace simpleThread {
    class TaskQueue {
    private:
        // 任务队列
        std::deque<Task *> queue;
        // 任务读写锁
        std::timed_mutex mtx;
        // 获取阻塞时间(毫秒)
        int const PULL_WAIT = 50;

        Task *popTask() noexcept;

    public:
        void push(Task *task);

        Task *pull();

        void reset();

        unsigned long size();
    };
}

#endif //SIMPLE_THREAD_CPP_TASK_QUEUE_H
