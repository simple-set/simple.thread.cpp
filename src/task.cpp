#include "task.h"

namespace simpleThread {
    Task::Task(Runnable *runnable) : runnable(runnable) {
        this->type = taskKind::runnable;
    }

    taskKind Task::getType() const {
        return this->type;
    }

    Runnable *Task::getRunnable() const {
        return this->runnable;
    }
}