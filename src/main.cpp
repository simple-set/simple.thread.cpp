#include <iostream>
#include "task.h"
#include "task_queue.h"
#include "process.h"
#include <thread>
#include "STL_thread.h"


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
    Test test;
    simpleThread::Task task{};
    task.setRunnable(&test);

    simpleThread::TaskQueue queue;
    queue.push(&task);

    // auto process = simpleThread::Process();
    // process.setQueue(&queue);
    // process.work();
    // process.setDone();

    simpleThread::STLThread thread(&queue);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // thread.join();
    thread.shutdown();

    //
    // return 0;
}