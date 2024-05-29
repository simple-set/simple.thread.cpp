//
// Created by xk on 2024/5/28.
//

#ifndef SIMPLE_THREAD_CPP_TASK_H
#define SIMPLE_THREAD_CPP_TASK_H

namespace simpleThread {
    class Task {
    public:
        virtual void run() = 0;
    };
}

namespace simpleThread {
    template<class T>
    class Callable {
    public:
        virtual T call() = 0;
    };
}
#endif //SIMPLE_THREAD_CPP_TASK_H
