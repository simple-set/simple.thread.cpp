#include <iostream>
#include "process.h"

namespace simpleThread {
    Process::Process(TaskQueue *queue) {
        if (queue != nullptr) {
            this->queue = queue;
        }
    }

    Task *Process::getTask() const noexcept {
        if (this->mtx->try_lock_for(std::chrono::milliseconds(this->POLL_TIME))) {
            return this->queue->pull();
        } else {
            return nullptr;
        }
    }

    void Process::work() const noexcept {
        while (!this->done) {
            Task *task = this->getTask();

            if (task != nullptr) {
                Process::doWork(task);
            }
        }
    }

    void Process::doWork(Task *task) noexcept {
        try {
            if (task->getType() == taskType::runnable) {
                task->getRunnable()->run();
            }
        } catch (std::exception &e) {
            std::cerr << "err: " << e.what() << std::endl;
        }
    }

    void Process::setDone() {
        this->done = true;
    }
}
