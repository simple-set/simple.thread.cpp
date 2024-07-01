#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef SIMPLE_THREAD_CPP_STL_THREAD_H
#define SIMPLE_THREAD_CPP_STL_THREAD_H

#include <thread>
#include <ctime>
#include <functional>
#include "task_queue.h"
#include "logger.h"
#include "thread_state.h"

namespace simpleThread {
    class STLThread {
    private:
        Log *logger = loggerFactory();

        // 工作线程
        std::thread workThread;

        // 任务队列
        TaskQueue *queue;

        // 阻塞线程, 等待所有任务完成
        volatile bool isJoin = false;

        // 线程状态
        volatile ThreadState state = ready;

        // 线程名称
        std::string threadName;

        // 设置线程名
        void setThreadName(std::string const &prefix);

        // 线程id
        std::thread::id threadId;

        void setThreadId();

        // 线程最近执行时间戳, 用于空闲回收
        time_t executeTime = std::time(nullptr);

        // 从管理器中移出线程
        std::function<bool(STLThread &)> removeThread;

        // 启动工作线程
        void start();

        // 执行队列任务
        void execute();

        bool isBreak();

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

        void setExit();

        bool isExit();

        volatile ThreadState getState() const;

        void setRemoveThread(const std::function<bool(STLThread &)> &function);
    };
}

#endif //SIMPLE_THREAD_CPP_STL_THREAD_H

#pragma clang diagnostic pop