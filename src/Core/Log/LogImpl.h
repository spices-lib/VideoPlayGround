#pragma once
#include "Core/NonCopyable.h"
#include "Log.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // This Macro must be defined.
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace PlayGround {

    class LogImpl : public Log
    {
    public:

        LogImpl();
        ~LogImpl() override;

        void CoreTrace   (const std::string& msg) override;
        void CoreInfo    (const std::string& msg) override;
        void CoreWarn    (const std::string& msg) override;
        void CoreError   (const std::string& msg) override;
        void CoreCritical(const std::string& msg) override;

        void ClientTrace   (const std::string& msg) override;
        void ClientInfo    (const std::string& msg) override;
        void ClientWarn    (const std::string& msg) override;
        void ClientError   (const std::string& msg) override;
        void ClientCritical(const std::string& msg) override;

    private:

        std::shared_ptr<spdlog::logger> m_CoreLogger;
        std::shared_ptr<spdlog::logger> m_ClientLogger;
    };
}