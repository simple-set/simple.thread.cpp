#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include <ctime>
#include <functional>
#include "task_queue.h"

namespace simpleThread {
    class STLThread {
    private:
        // 任务线程
        std::thread workThread;

        // 任务队列
        TaskQueue *queue;

        // 阻塞线程, 等待所有任务完成后退出线程
        bool volatile done = false;

        // 关闭线程, 不在执行新任务, 等待退出
        bool volatile shutdown = false;

        // 退出线程, 等待回收
        bool volatile exit = false;

        // 线程名称
        std::string threadName;

        // 线程最近执行时间戳
        time_t executeTime = std::time(nullptr);

        // 生成线程名称
        std::string makeThreadName(std::string const &prefix);

        // 从管理器中移出线程
        std::function<bool(STLThread &)> removeThread;

        // 启动工作线程
        void start();

        // 执行队列任务
        void execute();

        bool isShutdown();

        // 执行业务
        static void work(const std::function<void()> &) noexcept;

    public:
        explicit STLThread(TaskQueue *, const std::string &);
        ~STLThread();

        std::thread::id getId();

        time_t getExecuteTime() const;

        // 阻塞线程, 等待所有任务完成
        void join();

        // 关闭线程, 丢弃未执行的任务
        void setShutdown();

        // 分离线程, 设置为daemon模式
        void setDaemon();

        void setRemoveThread(const std::function<bool(STLThread &)> &function);

        volatile bool getExit() const;

        volatile bool getShutdown() const;
    };
}

#endif //SIMPLE_THREAD_CPP_STL_THREAD_H

#pragma clang diagnostic pop