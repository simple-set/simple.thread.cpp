#include "thread_factory.h"

namespace simpleThread {
    WorkThread *ThreadFactory::create() noexcept {
        std::lock_guard<std::mutex> lock(this->mtx);
        return new WorkThread;
    }
}
