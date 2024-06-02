#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-avoid-bind"

#include "thread_manage.h"

namespace simpleThread {
    ThreadManage::ThreadManage(int coreSize, int maxSize, TaskQueue *queue)
            : coreSize(coreSize), maxSize(maxSize), queue(queue) {}

    STLThread *ThreadManage::makeThread() {
        STLThread *thread = this->factory.create(this->queue);
        thread->setMaxSize(&this->maxSize);
        thread->setCoreSize(&this->coreSize);
        thread->setActivateSiz(&this->activateSiz);

        auto removeThread = std::bind(&ThreadManage::removeThread, this, std::placeholders::_1);
        thread->setRemoveThread(removeThread);

        return thread;
    }

    void ThreadManage::initThreads() {
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        for (int i = 0; i < this->getCoreSize(); ++i) {
            this->addThread();
        }
    }

    void ThreadManage::addThread() {
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        STLThread *thread = this->makeThread();
        this->threads.insert(std::make_pair(thread->getId(), thread));
        this->activateSiz++;
    }

    void ThreadManage::removeThread(STLThread *thread) {
        std::lock_guard<std::recursive_mutex> lock(this->mtx);
        this->threads.erase(thread->getId());
        this->activateSiz--;
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
}

#pragma clang diagnostic pop