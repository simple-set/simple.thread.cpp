#include <iostream>
#include <sstream>
#include "STL_thread.h"
#include "logger.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
namespace simpleThread {
    STLThread::STLThread(TaskQueue *queue, const std::string &name) : queue(queue) {
        this->workThread = std::thread(&STLThread::start, std::ref(*this));
        this->setThreadId();
        this->setThreadName(name);
        this->logger->debug("create thread {}", this->threadName);
    }

    STLThread::~STLThread() {
        this->logger->debug("Destroy thread {}", this->threadName);
    }

    void STLThread::start() {
        this->execute();
        this->logger->debug("exit thread {}", this->threadName);
    }

    void STLThread::execute() {
        while (!this->isExit()) {
            auto task = this->queue->pull();

            if (task != nullptr) {
                this->state = activate;
                STLThread::work(task);
                this->executeTime = std::time(nullptr);
                this->state = ready;
                continue;
            }
            if (this->isBreak()) {
                return;
            }
        }
    }

    void STLThread::work(const std::function<void()> &task) noexcept {
        try {
            task();
        } catch (std::exception &e) {
            loggerFactory()->warn("execute task error: ", e.what());
        }
    }

    std::thread::id STLThread::getId() {
        return this->threadId;
    }

    void STLThread::join() {
        this->isJoin = true;
        if (this->workThread.joinable()) {
            this->workThread.join();
        }
    }

    void STLThread::shutdown() {
        this->setExit();
    }

    bool STLThread::isExit() {
        return this->state == close;
    }

    void STLThread::setExit() {
        if (this->workThread.joinable()) {
            this->workThread.detach();
        }
        this->state = close;
    }

    bool STLThread::isBreak() {
        if (this->removeThread != nullptr && this->removeThread(*this)) {
            // 线程空闲超时
            this->setExit();
            return true;
        }

        if (this->isJoin && this->queue->size() <= 0) {
            this->setExit();
            return true;
        }

        if (this->isExit()) {
            // 线程已退出
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

    void STLThread::setThreadName(std::string const & prefix) {
        std::ostringstream oss;
        oss << this->getId();
        this->threadName =  prefix + "-" + oss.str();
    }

    void STLThread::setThreadId() {
        this->threadId = this->workThread.get_id();
    }

    volatile ThreadState STLThread::getState() const {
        return state;
    }
}
#pragma clang diagnostic pop