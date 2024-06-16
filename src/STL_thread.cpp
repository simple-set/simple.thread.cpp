#include <iostream>
#include <sstream>
#include "STL_thread.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
namespace simpleThread {

    STLThread::STLThread(TaskQueue *queue, const std::string &name) : queue(queue) {
        this->workThread = std::thread(&STLThread::start, std::ref(*this));
        this->threadName = this->makeThreadName(name);
        this->threadId = this->workThread.get_id();
    }

    void STLThread::start() {
        std::cout << "create thread: " << this->threadName << std::endl;
        this->execute();
        std::cout << "destroy  thread: " << this->threadName << std::endl;
    }

    void STLThread::execute() {
        while (!this->exit) {
            auto task = this->queue->pull();

            if (task != nullptr) {
                STLThread::work(task);
                this->executeTime = std::time(nullptr);
                continue;
            }
            if (this->isContinue()) {
                return;
            }
        }
    }

    void STLThread::work(const std::function<void()> &task) noexcept {
        try {
            task();
        } catch (std::exception &e) {
            std::cerr << "execute task error: " << e.what() << std::endl;
        }
    }

    std::thread::id STLThread::getId() {
        return this->threadId;
    }

    void STLThread::join() {
        this->done = true;
        if (this->workThread.joinable()) {
            this->workThread.join();
        }
        this->setExit(true);
    }

    void STLThread::shutdown() {
        this->setExit(true);
    }

    void STLThread::setDaemon() {
        if (this->workThread.joinable()) {
            this->workThread.detach();
        }
    }

    bool STLThread::isContinue() {
        if (this->removeThread != nullptr && this->removeThread(*this)) {
            this->setExit(true);
            return true;
        }
        if (this->done && this->queue->size() <= 0) {
            return true;
        }
        return false;
    }

    void STLThread::setRemoveThread(const std::function<bool(STLThread &)> &function) {
        STLThread::removeThread = function;
    }

    time_t STLThread::getExecuteTime() const {
        return executeTime;
    }

    std::string STLThread::makeThreadName(std::string const &prefix) {
        std::ostringstream oss;
        oss << this->workThread.get_id();
        return prefix + "-" + oss.str();
    }

    STLThread::~STLThread() {
        std::cout << "~STLThread: " << this->threadName << std::endl;
    }

    volatile bool STLThread::getExit() const {
        return this->exit;
    }

    void STLThread::setExit(volatile bool exit) {
        this->setDaemon();
        STLThread::exit = exit;
    }
}
#pragma clang diagnostic pop