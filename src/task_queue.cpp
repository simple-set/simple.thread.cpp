#include "task_queue.h"

namespace simpleThread {
    void TaskQueue::push(const std::function<void()>& call) {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->cv.notify_all();
        if (!this->close) {
            this->queue.push_back(call);
        }
    }

    std::function<void()> TaskQueue::pull() {
        std::unique_lock<std::mutex> lock(this->mtx);
        auto task = this->popTask();
        if (task == nullptr && !this->close) {
            this->cv.wait_for(lock, std::chrono::milliseconds(this->PULL_WAIT));
        }
        return task;
    }

    std::function<void()> TaskQueue::popTask() noexcept {
        if (this->size() > 0) {
            auto task = this->queue.front();
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

    void TaskQueue::setClose() {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->cv.notify_all();
        TaskQueue::close = true;
    }

    volatile bool TaskQueue::isClose() const {
        return this->close;
    }
}