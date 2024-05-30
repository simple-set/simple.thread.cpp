#ifndef SIMPLE_THREAD_CPP_TASK_QUEUE_H
#define SIMPLE_THREAD_CPP_TASK_QUEUE_H
#include "task.h"

namespace simpleThread {
    class TaskQueue {
    public:
        void push(Task *task) const;
        Task* pull();
    };
}

#endif //SIMPLE_THREAD_CPP_TASK_QUEUE_H
