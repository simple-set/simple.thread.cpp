#include "task.h"

namespace simpleThread {
    void Task::setType(taskKind kind) {
        Task::type = kind;
    }

    taskKind Task::getType() const {
        return this->type;
    }

    void Task::setRunnable(Runnable *run) {
        this->setType(taskKind::runnable);
        Task::runnable = run;
    }

    Runnable *Task::getRunnable() const {
        return this->runnable;
    }
}