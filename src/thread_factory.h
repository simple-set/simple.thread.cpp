//
// Created by xk on 2024/5/28.
//

#ifndef SIMPLE_THREAD_CPP_THREAD_FACTORY_H
#define SIMPLE_THREAD_CPP_THREAD_FACTORY_H

#include <thread>
#include "thread.h"

namespace simpleThread {
    class ThreadFactory {
    private:
        std::mutex mux;
    public:
        simpleThread::thread *create() noexcept;
    };
}


// std::thread ThreadFactory() noexcept;

#endif //SIMPLE_THREAD_CPP_THREAD_FACTORY_H
