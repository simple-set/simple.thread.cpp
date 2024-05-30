#include <thread>
#include "thread.h"

simpleThread::WorkThread::WorkThread() {
    this->work = std::move(std::thread(&simpleThread::handler::process, std::ref(this->handler)));
}

auto simpleThread::WorkThread::getId() {
    return this->work.get_id();
}

void simpleThread::WorkThread::join() {
    if (this->work.joinable()) {
        this->work.join();
    }
}

void simpleThread::WorkThread::setDaemon() {
    if (this->work.joinable()) {
        this->work.detach();
    }
}
