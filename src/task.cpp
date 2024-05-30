#include "task.h"

void simpleThread::Task::setRunnable(simpleThread::Runnable *runnable) {
    Task::runnable = runnable;
}

void simpleThread::Task::setType(simpleThread::taskType type) {
    Task::type = type;
}

simpleThread::taskType simpleThread::Task::getType() const {
    return type;
}

simpleThread::Runnable *simpleThread::Task::getRunnable() const {
    return runnable;
}