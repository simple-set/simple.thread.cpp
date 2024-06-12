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

void MyEcho() {
    printf("echo\n");
}

void MyPrintf(const std::string& data) {
    printf("%s\n", data.c_str());
}

template<class F, class... Args>
void execute(F &&f, Args &&... args) {
   // using return_type = typename std::result_of<F(Args...)>::type;
   // std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
   // std::future<return_type> res = task.get_future();

   // task();
   // return res;
   //  std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto call = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    call();
}

int main() {
   Test test;
//    simpleThread::Task task(&test);

   simpleThread::TaskQueue queue;
   queue.push([obj=&test](){obj->run();});
   queue.push([]{MyEcho();});
   auto task1 = queue.pull();
   auto task2 = queue.pull();
   auto task3 = queue.pull();
   task1();
   task2();

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
    // simpleThread::ThreadPool pool(4, 16);
    // pool.execute(MyEcho);
    // pool.execute([object = &test](){object->run();});
    // pool.execute(MyPrintf, "test");
    // for (int i = 0; i < 100; ++i) {
//        pool.execute(&test);
//         pool.execute([object = &test] { object->run(); });
//     }
    // pool.join();
    // pool.shutdown();
    // pool.execute([object = &test](){object->run();});
    // pool.execute(MyEcho);
    // std::cout << "end"  << std::endl;

    // execute([object = &test](){object->run();});
    // execute(MyEcho);
    // execute(MyPrintf, "test");
    return 0;
}