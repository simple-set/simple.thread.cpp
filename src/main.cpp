#include <iostream>
#include "task.h"
#include "task_queue.h"
#include "process.h"
#include <thread>
#include "STL_thread.h"
#include "thread_factory.h"
#include "thread_pool.h"


class Test : public simpleThread::Runnable {
public:
    void run() override {
        for (int i = 0; i < 3; ++i) {
            std::cout << "tid: " << std::this_thread::get_id() << ", test" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};


int main() {
//    Test test;
//    simpleThread::Task task(&test);

//    simpleThread::TaskQueue queue;
//    queue.push(&task);

    // auto process = simpleThread::Process();
    // process.setQueue(&queue);
    // process.workThread();
    // process.setDone();

//    simpleThread::STLThread thread(&queue);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    thread.shutdown();
//    thread.join();

//    simpleThread::ThreadFactory factory;
//    auto thread = factory.create(&queue, nullptr);
//    thread->shutdown();
//    thread->join();
//    delete thread;


    Test test;
    simpleThread::ThreadPool pool;
    pool.execute(&test);
    pool.execute(&test);
    pool.join();
    std::cout << "end" << std::endl;
     return 0;
}