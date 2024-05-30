#include "process.h"

namespace simpleThread {
    [[noreturn]] void process::work() const noexcept {
        while (true) {

        }
    }

    Task *process::getTask() noexcept {
        // std::unique_lock<std::mutex> lock(*this->mtx, std::try);


        // std::lock_guard<std::mutex> lock(*this->mux);
        return this->queue->pull();
    }

    void process::done() noexcept {

    }
}
