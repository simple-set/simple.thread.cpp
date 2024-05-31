#include <iostream>
#include "process.h"

namespace simpleThread {
    void Process::setDone() {
        this->done = true;
    }

    void Process::setShutdown() {
        this->shutdown = true;
    }

    void Process::setQueue(TaskQueue *taskQueue) {
        Process::queue = taskQueue;
    }

    Task *Process::getTask() const noexcept {
        return this->queue->pull();
    }

    void Process::work() const noexcept {
        while (!this->shutdown) {
            Task *task = this->getTask();

            if (task != nullptr) {
                Process::executeTask(task);
            } else if (this->done) {
                return;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(this->WAIT_TIME));
            }
        }
    }

    void Process::executeTask(Task *task) noexcept {
        try {
            if (task->getType() == taskKind::runnable) {
                task->getRunnable()->run();
            }
        } catch (std::exception &e) {
            std::cerr << "err: " << e.what() << std::endl;
        }
    }
}
