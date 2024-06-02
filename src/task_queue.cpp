#include "task_queue.h"

namespace simpleThread {
    void TaskQueue::push(Task *task) {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->cv.notify_all();
        if (!this->close) {
            this->queue.push_back(task);
        }
    }

    Task *TaskQueue::pull() {
        std::unique_lock<std::mutex> lock(this->mtx);
        Task *task = this->popTask();
        if (task == nullptr && !this->close) {
            this->cv.wait_for(lock, std::chrono::milliseconds(this->PULL_WAIT));
        }
        return task;
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
        std::lock_guard<std::mutex> lock(this->mtx);
        this->queue.clear();
    }

    unsigned long TaskQueue::size() {
        return this->queue.size();
    }

    bool TaskQueue::getClose() const {
        return close;
    }

    void TaskQueue::setClose() {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->cv.notify_all();
        TaskQueue::close = true;
    }
}