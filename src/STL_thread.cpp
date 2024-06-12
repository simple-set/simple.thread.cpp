#include <iostream>
#include "STL_thread.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
namespace simpleThread {

    STLThread::STLThread(TaskQueue *queue) : queue(queue) {
        this->workThread = std::move(std::thread(&STLThread::start, std::ref(*this)));
    }

    void STLThread::start() {
        this->execute();
        if (this->removeThread != nullptr) {
            // 执行结束, 移出线程
            this->removeThread(this);
        }
    }

    void STLThread::execute() {
        while (!this->exit) {
            auto task = this->queue->pull();

            if (task != nullptr) {
                STLThread::work(task);
                this->executeTime = std::time(nullptr);
                continue;
            }
            if (this->waitTimeout()) {
                // 超过空闲时间且活动线程大于核心线程数, 退出当前线程
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

    void STLThread::shutdown() {
        this->exit = true;
        this->setDaemon();
    }

    void STLThread::setDaemon() {
        if (this->workThread.joinable()) {
            this->workThread.detach();
        }
    }

    bool STLThread::waitTimeout() const {
        if (coreSize == nullptr || maxSize == nullptr || activateSiz == nullptr) {
            return false;
        }
        if (this->freeTime() && *activateSiz > *coreSize) {
            return true;
        }
        return false;
    }

    bool STLThread::freeTime() const {
        return (std::time(nullptr) - this->executeTime) > this->IDLE_EXIT_TIME;
    }

    void STLThread::setRemoveThread(const std::function<void(STLThread *)> &function) {
        STLThread::removeThread = function;
    }

    void STLThread::setCoreSize(const int *size) {
        STLThread::coreSize = size;
    }

    void STLThread::setMaxSize(const int *size) {
        STLThread::maxSize = size;
    }

    void STLThread::setActivateSiz(const int *size) {
        STLThread::activateSiz = size;
    }
}
#pragma clang diagnostic pop