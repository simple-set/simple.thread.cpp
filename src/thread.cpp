#include <thread>
#include <iostream>
#include "task.cpp"

namespace simpleThread {
    class SimpleThread {
    private:
        std::thread work_thread;
        std::atomic_bool daemon;

        void start() const noexcept {
            while (true) {
                std::cout << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

    public:
        SimpleThread() noexcept: daemon(false) {
            this->work_thread = std::move(std::thread(&SimpleThread::start, this));
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
                this->work_thread.detach();
                this->daemon = true;
            }
        }

        void join() {
            if (this->work_thread.joinable()) {
                this->work_thread.join();
            }
        }
    };
}