//
// Created by xk on 2024/5/28.
//

#ifndef SIMPLE_THREAD_CPP_THREAD_FACTORY_H
#define SIMPLE_THREAD_CPP_THREAD_FACTORY_H

#include <thread>
#include <mutex>
#include "STL_thread.h"

namespace simpleThread {
    class ThreadFactory {
    private:
        std::mutex mtx;
    public:
        simpleThread::STLThread *create() noexcept;
    };
}


// std::STLThread ThreadFactory() noexcept;

#endif //SIMPLE_THREAD_CPP_THREAD_FACTORY_H
