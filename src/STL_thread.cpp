#include <iostream>
#include "STL_thread.h"

namespace simpleThread {
    auto STLThread::getId() {
        return this->work.get_id();
    }

    void STLThread::join() {
        if (this->work.joinable()) {
            this->process.setDone();
            this->work.join();
        }
    }

    void STLThread::setDaemon() {
        if (this->work.joinable()) {
            this->work.detach();
        }
    }

    void STLThread::shutdown() {
        this->process.setShutdown();
        this->setDaemon();
    }

    STLThread::STLThread(TaskQueue *queue): STLThread(queue, nullptr){}

    STLThread::STLThread(TaskQueue *queue, std::atomic_int *counter) : queue(queue), counter(counter) {
        this->process.setQueue(queue);
        this->createThread();
    }

    void STLThread::createThread() {
        this->work = std::move(std::thread(&STLThread::start, std::ref(*this)));
    }

    void STLThread::start() {
        if (this->counter != nullptr) {this->counter->store(1);}
        this->process.work();
        if (this->counter != nullptr) {this->counter->store(1);}
    }
}