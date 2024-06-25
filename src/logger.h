#ifndef SIMPLE_THREAD_CPP_LOGGER_H
#define SIMPLE_THREAD_CPP_LOGGER_H
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> loggerFactory();

#endif //SIMPLE_THREAD_CPP_LOGGER_H
