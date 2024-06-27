#include <iostream>
#include "task_queue.h"
#include "STL_thread.h"
#include "thread_factory.h"
#include "thread_pool.h"
#include "thread_manage.h"
#include "logger.h"


class Test  {
public:
    void run() {
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

std::thread::id getTid() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return std::this_thread::get_id();
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
//   Test test;
//    simpleThread::Task task(&test);

//   simpleThread::TaskQueue queue;
//   queue.push([obj=&test](){obj->run();});
//   queue.push([]{MyEcho();});
//   auto task1 = queue.pull();
//   auto task2 = queue.pull();
//   auto task3 = queue.pull();
//   task1();
//   task2();

//    simpleThread::STLThread thread(&queue);
//    thread.join();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    thread.shutdown();

//    simpleThread::ThreadFactory factory;
//    auto thread = factory.create(&queue);
//    thread->shutdown();
//    thread->join();
//    delete thread;

//    simpleThread::ThreadManage threadManage(1, 3, &queue);
//    threadManage.initThreads();
//    threadManage.join();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    threadManage.shutdown();


//     Test test;
//     simpleThread::ThreadPool pool(4, 16);
//     for (int i = 0; i < 100; ++i) {
//         pool.execute([object = &test] { object->run(); });
//     }
//     pool.join();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//     pool.shutdown();


    simpleThread::ThreadPool pool(1, 2);
    pool.execute(getTid);
//    auto result = pool.submit(getTid);
    pool.join();
    return 0;
}