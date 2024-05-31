#include "thread_factory.h"

namespace simpleThread {
    STLThread *ThreadFactory::create() noexcept {
        std::lock_guard<std::mutex> lock(this->mtx);
        // return new STLThread;
    }
}
