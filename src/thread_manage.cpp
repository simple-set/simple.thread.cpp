#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-avoid-bind"

#include "thread_manage.h"

namespace simpleThread {
    ThreadManage::ThreadManage(int coreSize, int maxSize, TaskQueue *queue)
            : coreSize(coreSize), maxSize(maxSize), queue(queue) {}

    STLThread *ThreadManage::makeThread() {
        auto* thread = new STLThread(queue, "thread");
        thread->setRemoveThread( std::bind(&ThreadManage::removeThread, this, std::placeholders::_1));
        return thread;
    }

    void ThreadManage::destroyThread() {
        for (const auto &thread: this->getThreadList()) {
            if (std::this_thread::get_id() == thread->getId()) {
                continue;
            }
            if (thread->getExit()) {
                this->threads.erase(thread->getId());
                this->activateSiz--;
                delete thread;
            }
        }
    }

    void ThreadManage::initThreads() {
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        for (int i = 0; i < this->getCoreSize(); ++i) {
            this->addThread();
        }
    }

    void ThreadManage::addThread() {
        if (this->close) {
            // 线程池已关闭,丢弃任务
            return;
        }
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        STLThread *thread = this->makeThread();
        this->threads.insert(std::make_pair(thread->getId(), thread));
        this->activateSiz++;
    }

    bool ThreadManage::removeThread(STLThread &thread) {
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        this->destroyThread();
        return this->threadTimeout(thread);
    }

    bool ThreadManage::threadTimeout(simpleThread::STLThread &thread) const {
        if (activateSiz > coreSize && (std::time(nullptr) - thread.getExecuteTime()) > this->IDLE_EXIT_TIME) {
            // 线程空闲时间过长且大于核心线程数
            return true;
        }
        if (thread.getExit()) {
            // 线程已经关闭
            return true;
        }
        return false;
    }

    void ThreadManage::setCoreSize(int size) {
        ThreadManage::coreSize = size;
    }

    void ThreadManage::setMaxSize(int size) {
        ThreadManage::maxSize = size;
    }

    int ThreadManage::getCoreSize() const {
        return coreSize;
    }

    int ThreadManage::getMaxSize() const {
        return maxSize;
    }

    int ThreadManage::getActivateSiz() const {
        return activateSiz;
    }

    void ThreadManage::join() {
        this->close = true;
        for (const auto &thread: this->getThreadList()) {
            thread->join();
        }
    }

    void ThreadManage::shutdown() {
        this->close = true;
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        for (const auto &thread: this->getThreadList()) {
            thread->shutdown();
        }
    }

    std::vector<STLThread *> ThreadManage::getThreadList() {
        std::vector<STLThread *> threadList;
        threadList.reserve(this->threads.size());
        for (const auto &item: this->threads) {
            threadList.push_back(item.second);
        }
        return threadList;
    }

    bool ThreadManage::getClose() const {
        return close;
    }

    ThreadManage::~ThreadManage() {
        this->destroyThread();
    }
}

#pragma clang diagnostic pop