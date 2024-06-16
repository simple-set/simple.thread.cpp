#include <iostream>
#include <sstream>
#include "STL_thread.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
namespace simpleThread {

    STLThread::STLThread(TaskQueue *queue, const std::string &name) : queue(queue) {
        this->workThread = std::thread(&STLThread::start, std::ref(*this));
        this->threadName = this->makeThreadName(name);
        std::cout << "create thread: " << this->threadName << std::endl;
    }

    void STLThread::start() {
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
            if (this->isShutdown()) {
                // 退出线程
                return;
            }
            if (this->done && this->queue->size() <= 0) {
                // 完成任务并退出线程
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
        return this->workThread.get_id();
    }

    void STLThread::join() {
        this->done = true;
        if (this->workThread.joinable()) {
            this->workThread.join();
        }
    }

    void STLThread::setShutdown() {
        this->exit = true;
        this->setDaemon();
    }

    void STLThread::setDaemon() {
        if (this->workThread.joinable()) {
            this->workThread.detach();
        }
    }

    bool STLThread::isShutdown() {
        if (this->removeThread != nullptr && this->removeThread(*this)) {
            // 已关闭的线程, 设置退出状态, 等待回收
            this->exit = true;
            this->setDaemon();
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
        std::cout << "~STLThread" << std::endl;
    }

    volatile bool STLThread::getExit() const {
        return this->exit;
    }

    volatile bool STLThread::getShutdown() const {
        return shutdown;
    }
}
#pragma clang diagnostic pop