#include <thread>
#include "thread.h"

simpleThread::thread::thread() {
    this->work = std::move(std::thread(&simpleThread::handler::process, std::ref(this->handler)));
}

auto simpleThread::thread::getId() {
    return this->work.get_id();
}

void simpleThread::thread::join() {
    if (this->work.joinable()) {
        this->work.join();
    }
}

void simpleThread::thread::setDaemon() {
    if (this->work.joinable()) {
        this->work.detach();
    }
}
