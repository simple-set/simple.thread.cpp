//
// Created by xk on 2024/5/28.
//

#include "thread_factory.h"

simpleThread::thread* simpleThread::thread_factory::create() {
    return new simpleThread::thread;
}
