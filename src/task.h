#ifndef SIMPLE_THREAD_CPP_TASK_H
#define SIMPLE_THREAD_CPP_TASK_H

#include <functional>

namespace simpleThread {
    enum class taskKind {
        runnable,
        callable,
        function
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
        Runnable *runnable{};
        std::function<void()> function;

    public:
        explicit Task(Runnable *);

        explicit Task(std::function<void()>);

        [[nodiscard]] taskKind getType() const;

        [[nodiscard]] Runnable *getRunnable() const;

        [[nodiscard]] const std::function<void()> &getFunction() const;

    };
}

#endif //SIMPLE_THREAD_CPP_TASK_H
