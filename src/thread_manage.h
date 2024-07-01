#ifndef SIMPLE_THREAD_CPP_THREAD_MANAGE_H
#define SIMPLE_THREAD_CPP_THREAD_MANAGE_H

#include <map>
#include <mutex>
#include "task_queue.h"
#include "STL_thread.h"

namespace simpleThread {
    /**
     * 线程管理器, 创建线程、关闭线程、维护线程状态等
     */
    class ThreadManage {
    private:
        // 互斥锁, 操作线程时保证安全
        std::recursive_mutex mtx;

        // 核心线程数
        int coreSize = 0;

        // 最大线程数
        int maxSize = 0;

        // 线程任务队列
        TaskQueue *queue = nullptr;

        // 线程池关闭状态
        bool volatile close = false;

        // 工作线程空闲退出时间(秒)
        int const IDLE_EXIT_TIME = 60;

        // 工作线程组
        std::map<std::thread::id, STLThread *> threads;

        std::vector<STLThread *> getThreadList();

        // 创建线程
        STLThread *makeThread();

        // 销毁已关闭的线程
        void destroyThread();

        // 移出工作线程
        bool removeThread(STLThread &thread);

        // 线程是否空闲超时
        bool threadTimeout(STLThread &thread);

    public:
        ThreadManage(int coreSize, int maxSize, TaskQueue *queue);

        ~ThreadManage();

        // 初始化线程, 创建核心线程数
        void initThreads();

        // 增加线程
        void addThread();

        // 等待线程完成任务
        void join();

        // 关闭线程, 丢弃未完成任务
        void shutdown();

        [[nodiscard]] bool getClose() const;

        void setCoreSize(int size);

        void setMaxSize(int size);

        [[nodiscard]] int getCoreSize() const;

        [[nodiscard]] int getMaxSize() const;

        // 等待线程数
        int getReadySize();

        // 总线程数
        int getTotal();
    };
}

#endif //SIMPLE_THREAD_CPP_THREAD_MANAGE_H
