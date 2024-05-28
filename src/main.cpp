#include <iostream>
#include <future>
#include "thread.cpp"

void process(threadPool::SimpleThread *thread) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    thread->SetDaemon();
}

void func1() {
    std::cout << "sleep, tid: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
}

void func2(std::thread *t) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (t->joinable()) {
        std::cout << "detach, tid: " << t->get_id() << std::endl;
        t->detach();
        std::cout << "detach, tid: " << t->get_id() << std::endl;
        std::cout << "joinable: " << t->joinable() << std::endl;
        // t->join();
        // std::cout << "joinable" << t->joinable() << t->joinable();
    }
}

int main() {
    std::thread t(func1);
    std::thread(func2, &t).detach();
    // std::thread(func2, &t).join();
    t.join();

    // std::cout << std::this_thread::get_id() << std::endl;
    // threadPool::SimpleThread thread;
    // std::thread(process, &thread).detach();
    // thread.join();
    return 0;
}