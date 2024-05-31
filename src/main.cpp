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

// void myFunction(void (*functionPtr)(int), int arg) {
//     functionPtr(arg);
// }

void myFunction(std::function<void(int)> function, int arg) {
    function(arg);
}

// 定义一个简单的函数
void exampleFunction(int x) {
    std::cout << "Example function called with: " << x << std::endl;
}

class MyClass {
public:
    void memberFunction(int arg) {
        std::cout << "Member function called with: " << arg << std::endl;
    }
};

void CallMemberFunction(std::function<void(int)> func, int arg) {
    func(arg); // 调用存储的函数
}

int main() {


    // MyClass myObject;
    // auto boundFunc = std::bind(&MyClass::memberFunction, &myObject, std::placeholders::_1);
    // CallMemberFunction(boundFunc, 5);

    // 调用myFunction，传递exampleFunction和参数
    // myFunction(exampleFunction, 5);

    Test test;
    simpleThread::Task task{};
    task.setRunnable(&test);

    simpleThread::TaskQueue queue;
    queue.push(&task);

    simpleThread::STLThread thread(&queue);
    // thread.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    thread.shutdown();
    //
    // auto process = simpleThread::Process();
    // process.setQueue(&queue);
    // process.work();
    // process.setDone();
    //
    // return 0;
}