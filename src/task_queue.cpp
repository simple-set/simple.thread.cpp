#include "task_queue.h"

namespace simpleThread {
    void TaskQueue::push(Task *task) {
        std::lock_guard<std::timed_mutex> lock(this->mtx);
        this->queue.push_back(task);
    }

    Task *TaskQueue::pull() {
        std::unique_lock<std::timed_mutex> lock(this->mtx, std::defer_lock);
        if (lock.try_lock_for(std::chrono::milliseconds(this->PULL_WAIT))) {
            return this->popTask();
        }
        return nullptr;
    }

    Task *TaskQueue::popTask() noexcept {
        if (this->size() > 0) {
            Task *task = this->queue.front();
            this->queue.pop_front();
            return task;
        }
        return nullptr;
    }

    void TaskQueue::reset() {
        std::lock_guard<std::timed_mutex> lock(this->mtx);
        this->queue.clear();
    }

    unsigned long TaskQueue::size() {
        return this->queue.size();
    }
}