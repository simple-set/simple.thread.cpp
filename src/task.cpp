#include "task.h"

namespace threadPool {
    template<typename T>
    class Task {
    public:
        virtual T run() = 0;
    };
}