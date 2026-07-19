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
inline void logi(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::info, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::info, fmt,
        std::forward<Args>(args)...);
}

template <typename... Args>
inline void logw(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::warn, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::warn, fmt,
        std::forward<Args>(args)...);
}

template <typename... Args>
inline void loge(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::err, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::err, fmt,
        std::forward<Args>(args)...);
}

template <typename... Args>
inline void logd(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::debug, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::debug, fmt,
        std::forward<Args>(args)...);
}

template <typename... Args>
inline void logt(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::trace, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::trace, fmt,
        std::forward<Args>(args)...);
}

template <typename... Args>
inline void logc(const char* file, int line, const char* function,
                 fmt::format_string<Args...> fmt, Args&&... args) {
    LogManager::GetInst().GetConsoleLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::critical, fmt,
        std::forward<Args>(args)...);
    LogManager::GetInst().GetFileLogger()->log(
        spdlog::source_loc{file, line, function}, spdlog::level::critical, fmt,
        std::forward<Args>(args)...);
}
//
// template <typename... Args>
// inline void LOGI(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_INFO(LogManager::GetInst().GetConsoleLogger(), fmt,
//                        std::forward<Args>(args)...);
//     SPDLOG_LOGGER_INFO(LogManager::GetInst().GetFileLogger(), fmt,
//                        std::forward<Args>(args)...);
// }
//
// template <typename... Args>
// inline void LOGW(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_WARN(LogManager::GetInst().GetConsoleLogger(), fmt,
//                        std::forward<Args>(args)...);
//     SPDLOG_LOGGER_WARN(LogManager::GetInst().GetFileLogger(), fmt,
//                        std::forward<Args>(args)...);
// }
//
// template <typename... Args>
// inline void LOGE(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_ERROR(LogManager::GetInst().GetConsoleLogger(), fmt,
//                         std::forward<Args>(args)...);
//     SPDLOG_LOGGER_ERROR(LogManager::GetInst().GetFileLogger(), fmt,
//                         std::forward<Args>(args)...);
// }
//
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
//
// template <typename... Args>
// inline void LOGC(fmt::format_string<Args...> fmt, Args&&... args) {
//     SPDLOG_LOGGER_CRITICAL(LogManager::GetInst().GetConsoleLogger(), fmt,
//                            std::forward<Args>(args)...);
//     SPDLOG_LOGGER_CRITICAL(LogManager::GetInst().GetFileLogger(), fmt,
//                            std::forward<Args>(args)...);
// }
}
