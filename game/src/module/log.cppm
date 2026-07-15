module;
#include <spdlog/spdlog.h>
export module log;

import std;

export class LogManager {
public:
    static LogManager& GetInst();

    auto& GetConsoleLogger() { return m_console_logger; }

    auto& GetFileLogger() { return m_file_logger; }

private:
    std::shared_ptr<spdlog::logger> m_console_logger;
    std::shared_ptr<spdlog::logger> m_file_logger;

    LogManager();

    static LogManager manager;
};

export {
template <typename... Args>
inline void LOGI(fmt::format_string<Args...> fmt, Args&&... args) {
    SPDLOG_LOGGER_INFO(LogManager::GetInst().GetConsoleLogger(), fmt,
                       std::forward<Args>(args)...);
    SPDLOG_LOGGER_INFO(LogManager::GetInst().GetFileLogger(), fmt,
                       std::forward<Args>(args)...);
}

template <typename... Args>
inline void LOGW(fmt::format_string<Args...> fmt, Args&&... args) {
    SPDLOG_LOGGER_WARN(LogManager::GetInst().GetConsoleLogger(), fmt,
                       std::forward<Args>(args)...);
    SPDLOG_LOGGER_WARN(LogManager::GetInst().GetFileLogger(), fmt,
                       std::forward<Args>(args)...);
}

template <typename... Args>
inline void LOGE(fmt::format_string<Args...> fmt, Args&&... args) {
    SPDLOG_LOGGER_ERROR(LogManager::GetInst().GetConsoleLogger(), fmt,
                        std::forward<Args>(args)...);
    SPDLOG_LOGGER_ERROR(LogManager::GetInst().GetFileLogger(), fmt,
                        std::forward<Args>(args)...);
}

// template <typename... Args>
// inline void LOGD(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_DEBUG(LogManager::GetInst().GetConsoleLogger(), fmt,
//                         std::forward<Args>(args)...);
//     SPDLOG_LOGGER_DEBUG(LogManager::GetInst().GetFileLogger(), fmt,
//                         std::forward<Args>(args)...);
// }
//
// template <typename... Args>
// inline void LOGT(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_TRACE(LogManager::GetInst().GetConsoleLogger(), fmt,
//                         std::forward<Args>(args)...);
//     SPDLOG_LOGGER_TRACE(LogManager::GetInst().GetFileLogger(), fmt,
//                         std::forward<Args>(args)...);
// }

template <typename... Args>
inline void LOGC(fmt::format_string<Args...> fmt, Args&&... args) {
    SPDLOG_LOGGER_CRITICAL(LogManager::GetInst().GetConsoleLogger(), fmt,
                           std::forward<Args>(args)...);
    SPDLOG_LOGGER_CRITICAL(LogManager::GetInst().GetFileLogger(), fmt,
                           std::forward<Args>(args)...);
}
}
