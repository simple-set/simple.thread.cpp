#include <thread>
#include <iostream>
#include "task.cpp"

namespace threadPool {
    class SimpleThread {
    private:
        std::thread work_thread;
        std::atomic_bool daemon;
        std::__thread_id tid;

        void start() const noexcept {
            while (true) {
                std::cout << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

    public:
        SimpleThread() noexcept: daemon(false) {
            this->work_thread = std::move(std::thread(&SimpleThread::start, this));
            this->tid = work_thread.get_id();
        }

        ~SimpleThread() {
            if (this->work_thread.joinable()) {
                this->work_thread.detach();
            }
        }

        auto GetId() const {
            return this->work_thread.get_id();
        }

        void SetDaemon() {
            if (this->work_thread.joinable()) {
                std::cout << "setDaemon" << std::endl;
                this->work_thread.detach();
                this->daemon = true;
                std::cout << "joinable: " << work_thread.joinable() << std::endl;
            }
        }

        void join() {
            if (this->work_thread.joinable()) {
                std::cout << "join" << std::endl;
                this->work_thread.join();
                std::cout << "join" << std::endl;
            }
        }
    };
}