#include <iostream>
#include <sstream>
#include "STL_thread.h"
#include "logger.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
namespace simpleThread {
    STLThread::STLThread(TaskQueue *queue, const std::string &name) : queue(queue) {
        this->threadNamePrefix = name;
        this->workThread = std::thread(&STLThread::start, std::ref(*this));
        this->setThreadId();
    }

    STLThread::~STLThread() {
        this->logger->debug("Destroy thread {}", this->threadName);
    }

    void STLThread::start() {
        this->setThreadName();
        this->logger->debug("create thread {}", this->threadName);
        this->execute();
        this->logger->debug("exit thread {}", this->threadName);
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
            loggerFactory()->warn("execute task error: ", e.what());
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

    void STLThread::setThreadName() {
        std::ostringstream oss;
        oss << this->workThread.get_id();
        this->threadName =  this->threadNamePrefix + "-" + oss.str();
    }

    void STLThread::setThreadId() {
        this->threadId = this->workThread.get_id();
//        this->threadId = std::this_thread::get_id();
//        this->threadId =
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