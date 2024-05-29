#ifndef SIMPLE_THREAD_CPP_THREAD_H
#define SIMPLE_THREAD_CPP_THREAD_H

#include <thread>
#include "handler.h"

namespace simpleThread {
    class thread {
    private:
        std::thread work;
        simpleThread::handler handler;
    public:
        thread();

        ~thread() = default;

        auto getId();

        void join();

        void setDaemon();
    };
}


#endif //SIMPLE_THREAD_CPP_THREAD_H
