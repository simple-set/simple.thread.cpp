#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include <ctime>
#include <functional>
#include "task_queue.h"
#include "logger.h"

namespace simpleThread {
    class STLThread {
    private:
        Log* logger = loggerFactory();

        // 任务线程
        std::thread workThread;

        // 任务队列
        TaskQueue *queue;

        // 阻塞线程, 等待所有任务完成
        bool volatile done = false;

        // 退出线程
        bool volatile exit = false;

        // 线程名称
        std::string threadName;

        // 线程id
        std::thread::id threadId;

        // 线程最近执行时间戳, 用于空闲回收
        time_t executeTime = std::time(nullptr);

        // 生成线程名称
        std::string makeThreadName(std::string const &prefix);

        // 从管理器中移出线程
        std::function<bool(STLThread &)> removeThread;

        // 启动工作线程
        void start();

        // 执行队列任务
        void execute();

        bool isContinue();

        // 分离线程, 设置为daemon模式
        void setDaemon();

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
        void shutdown();

        void setRemoveThread(const std::function<bool(STLThread &)> &function);

        void setExit(volatile bool exit);

        volatile bool getExit() const;
    };
}

#endif //SIMPLE_THREAD_CPP_STL_THREAD_H

#pragma clang diagnostic pop