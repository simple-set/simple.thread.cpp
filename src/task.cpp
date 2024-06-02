#include "task.h"

#include <utility>

namespace simpleThread {
    Task::Task(Runnable *runnable) : runnable(runnable) {
        this->type = taskKind::runnable;
    }

    Task::Task(std::function<void()> function) : function(std::move(function)) {
        this->type = taskKind::function;
    }

    taskKind Task::getType() const {
        return this->type;
    }

    Runnable *Task::getRunnable() const {
        return this->runnable;
    }

    const std::function<void()> &Task::getFunction() const {
        return this->function;
    }
}