#include <iostream>
#include "STL_thread.h"

namespace simpleThread {
    auto STLThread::getId() {
        return this->workThread.get_id();
    }

    void STLThread::join() {
        if (this->workThread.joinable()) {
            this->process.setDone();
            this->workThread.join();
        }
    }

    void STLThread::setDaemon() {
        if (this->workThread.joinable()) {
            this->workThread.detach();
        }
    }

    void STLThread::shutdown() {
        this->process.setShutdown();
        this->setDaemon();
    }

    STLThread::STLThread(TaskQueue *queue): STLThread(queue, nullptr){}

    STLThread::STLThread(TaskQueue *queue, std::atomic_int *counter) : queue(queue), counter(counter) {
        this->process.setQueue(queue);
        this->start();
    }

    void STLThread::start() {
        this->workThread = std::move(std::thread(&STLThread::execute, std::ref(*this)));
    }

    void STLThread::execute() {
        if (this->counter != nullptr) {this->counter->fetch_add(1);}
        this->process.work();
        if (this->counter != nullptr) {this->counter->fetch_sub(1);}
    }
}