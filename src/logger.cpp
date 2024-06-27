#include <iostream>
#include "logger.h"

namespace simpleThread {

    static Log *defaultLogger = nullptr;

    Log *loggerFactory() {
        if (defaultLogger == nullptr) {
            defaultLogger = new Log(spdlog::stdout_color_mt("console"));
        }
        return defaultLogger;
    }
}