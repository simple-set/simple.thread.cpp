//
// Created by xk on 2024/5/28.
//

#include "thread_factory.h"

namespace simpleThread {
    thread *ThreadFactory::create() noexcept {
        std::lock_guard<std::mutex> lock(this->mux);
        return new thread;
    }
}
