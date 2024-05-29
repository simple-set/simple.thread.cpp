#ifndef SIMPLE_THREAD_CPP_TASK_H
#define SIMPLE_THREAD_CPP_TASK_H

namespace simpleThread {
    enum class taskType {
        runnable,
        callable
    };

    class Runnable {
    public:
        virtual void run() = 0;
    };

    template<class T>
    class Callable {
    public:
        virtual T call() = 0;
    };

    class Task {
    private:
        taskType type;
        Runnable *runnable;

    public:
        void setType(taskType type);

    public:
        void setRunnable(Runnable *runnable);
    };
}

#endif //SIMPLE_THREAD_CPP_TASK_H
