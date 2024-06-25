#include "logger.h"

std::shared_ptr<spdlog::logger> loggerFactory() {
    return  spdlog::stdout_color_mt("console");
}
