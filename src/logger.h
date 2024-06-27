#ifndef SIMPLE_THREAD_CPP_LOGGER_H
#define SIMPLE_THREAD_CPP_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace simpleThread {
    class Log {

    private:
        std::shared_ptr<spdlog::logger> logger;
        spdlog::level::level_enum logLevel = spdlog::level::debug;
        std::string logFormat = "%Y-%m-%d %H:%M:%S.%e %l %n pid:%P tid:%t %v";

    public:
        explicit Log(const std::shared_ptr<spdlog::logger> &logger) : logger(logger){
            this->logger->set_level(logLevel);
            this->logger->set_pattern(this->logFormat);
        };

        void setLevelEnum(spdlog::level::level_enum level) {
            this->logLevel = level;
            this->logger->set_level(level);
        }

        void setLogFormat(const std::string &format) {
            this->logFormat = format;
            this->logger->set_pattern(this->logFormat);
        }

        template<typename ...Args>
        void debug(const char *message, Args &&...args) {
            this->logger->debug(message, std::forward<Args>(args)...);
        };

        template<typename ...Args>
        void info(const char *message, Args &&...args) {
            this->logger->info(message, std::forward<Args>(args)...);
        };

        template<typename ...Args>
        void warn(const char *message, Args &&...args) {
            this->logger->warn(message, std::forward<Args>(args)...);
        };

        template<typename ...Args>
        void error(const char *message, Args &&...args) {
            this->logger->error(message, std::forward<Args>(args)...);
        };
    };

    Log *loggerFactory();
}
#endif //SIMPLE_THREAD_CPP_LOGGER_H
