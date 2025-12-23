#include "LogImpl.h"
#include "Console.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include <time.h>

namespace PlayGround {

    LogImpl::LogImpl() : Log()
    {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l] %v");
        spdlog::flush_every(std::chrono::seconds(5));

        auto max_size = 1048576 * 5;
        auto max_files = 3;

        const auto ide_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        ide_console_sink->set_level(spdlog::level::trace);

        const auto console_sink = Console::Registry("Console");

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(ide_console_sink);
        sinks.push_back(console_sink);

        m_CoreLogger = std::make_shared<spdlog::logger>("Engine", begin(sinks), end(sinks));
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = std::make_shared<spdlog::logger>("Game", begin(sinks), end(sinks));
        m_ClientLogger->set_level(spdlog::level::trace);

        m_IsInitialized = true;
    }

    LogImpl::~LogImpl ()
    {
        m_IsInitialized = false;

        m_CoreLogger.reset();
        m_ClientLogger.reset();
        spdlog::drop_all();
    }

    void LogImpl::CoreTrace     (const std::string& msg) { m_CoreLogger->trace   (msg); }
    void LogImpl::CoreInfo      (const std::string& msg) { m_CoreLogger->info    (msg); }
    void LogImpl::CoreWarn      (const std::string& msg) { m_CoreLogger->warn    (msg); }
    void LogImpl::CoreError     (const std::string& msg) { m_CoreLogger->error   (msg); }
    void LogImpl::CoreCritical  (const std::string& msg) { m_CoreLogger->critical(msg); }

    void LogImpl::ClientTrace   (const std::string& msg) { m_CoreLogger->trace   (msg); }
    void LogImpl::ClientInfo    (const std::string& msg) { m_CoreLogger->info    (msg); }
    void LogImpl::ClientWarn    (const std::string& msg) { m_CoreLogger->warn    (msg); }
    void LogImpl::ClientError   (const std::string& msg) { m_CoreLogger->error   (msg); }
    void LogImpl::ClientCritical(const std::string& msg) { m_CoreLogger->critical(msg); }
}