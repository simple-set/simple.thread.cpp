#ifndef SIMPLE_THREAD_CPP_THREAD_H
#define SIMPLE_THREAD_CPP_THREAD_H

#include <thread>
#include "handler.h"

namespace simpleThread {
    class WorkThread {
    private:
        std::thread work;
        simpleThread::handler handler;
    public:
        WorkThread();

        ~WorkThread() = default;

        auto getId();

        void join();

        void setDaemon();
    };
}


#endif //SIMPLE_THREAD_CPP_THREAD_H
