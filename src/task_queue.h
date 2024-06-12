#ifndef SIMPLE_THREAD_CPP_TASK_QUEUE_H
#define SIMPLE_THREAD_CPP_TASK_QUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include "task.h"

namespace simpleThread {
    class TaskQueue {
    private:
        // 任务队列
        std::deque<std::function<void()>> queue;

        // 关闭标志位
        bool volatile close = false;

        // 任务读写锁
        std::mutex mtx;

        // 条件变量
        std::condition_variable cv;

        // 获取阻塞时间(毫秒)
        int const PULL_WAIT = 2000;

        std::function<void()> popTask() noexcept;

    public:
        void push(const std::function<void()>&);

        std::function<void()> pull();

        [[nodiscard]] bool getClose() const;

        void setClose();

        void reset();

        unsigned long size();
    };
}

#endif //SIMPLE_THREAD_CPP_TASK_QUEUE_H
