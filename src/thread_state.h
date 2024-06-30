#ifndef SIMPLE_THREAD_CPP_THREAD_STATE_H
#define SIMPLE_THREAD_CPP_THREAD_STATE_H

/**
 * 线程状态
 */
enum ThreadState {
    // 活动, 正在执行任务中
    activate,
    // 等待
    wait
};

#endif //SIMPLE_THREAD_CPP_THREAD_STATE_H
