#ifndef SIMPLE_THREAD_CPP_TASK_H
#define SIMPLE_THREAD_CPP_TASK_H

namespace simpleThread {
    enum class taskKind {
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
        taskKind type;
        Runnable *runnable;

    public:
        explicit Task(Runnable *runnable);

        [[nodiscard]] taskKind getType() const;

        [[nodiscard]] Runnable *getRunnable() const;
    };
}

#endif //SIMPLE_THREAD_CPP_TASK_H
