#include <iostream>
#include "task.h"
#include "task_queue.h"
//#include <thread>
#include "STL_thread.h"
#include "thread_factory.h"
#include "thread_pool.h"
#include "thread_manage.h"


class Test : public simpleThread::Runnable {
public:
    void run() override {
        std::cout << "tid: " << std::this_thread::get_id() << ", Runnable, test" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};

time_t getTime() {
    return std::time(nullptr);
}

int main() {
//    Test test;
//    simpleThread::Task task(&test);
//
//    simpleThread::TaskQueue queue;
//    queue.push(&task);
//    queue.push(&task);
//    queue.push(&task);
//    queue.push(&task);

    // auto process = simpleThread::Process();
    // process.setQueue(&queue);
    // process.workThread();
    // process.setDone();

//    simpleThread::STLThread thread(&queue);
//    thread.join();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    thread.shutdown();

//    simpleThread::ThreadFactory factory;
//    auto thread = factory.create(&queue, nullptr);
//    thread->shutdown();
//    thread->join();
//    delete thread;

//    simpleThread::ThreadManage threadManage(1, 3, &queue);
//    threadManage.initThreads();
//    threadManage.join();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    threadManage.shutdown();


    // Test test;
    // simpleThread::ThreadPool pool(1, 16);
    // for (int i = 0; i < 100; ++i) {
    //     pool.execute([object = &test] { object->run(); });
    // }
    // pool.join();
    // pool.shutdown();


    simpleThread::ThreadPool pool(1);
    auto result = pool.submit<time_t>(&getTime);
    std::cout << "result: " << result.get() << std::endl;
    std::cout << "end"  << std::endl;
    return 0;
}