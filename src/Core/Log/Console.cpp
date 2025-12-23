#include "Console.h"

namespace PlayGround {

    static std::unordered_map<std::string, SP<Console>> m_GlobalConsolePool;

    Console::Console(uint32_t maxInfos)
            : m_MaxInfos(maxInfos)
    {}

    std::shared_ptr<Console> Console::Registry(const std::string& name)
    {
        if (m_GlobalConsolePool.find(name) == m_GlobalConsolePool.end())
        {
            m_GlobalConsolePool[name] = CreateSP<Console>();
        }

        return m_GlobalConsolePool[name];
    }

    void Console::Clear()
    {
        m_InfoData.Clear();
    }

    void Console::Push(const std::string& cmd)
    {
        // todo: To be completed.
        //m_LogInfos.push_back({ cmd , "info", glm::vec4(1.0f)});
    }

    void Console::sink_it_(const spdlog::details::log_msg& msg)
    {
        //std::lock_guard<std::mutex> lock(mutex_);

        std::stringstream ss;

        /**
        * @brief Get Log time.
        */
        time_t t = std::chrono::system_clock::to_time_t(msg.time);
        std::string times = ctime(&t);
        times.pop_back();

        /**
        * @brief Get Log level.
        */
        InfoLevelHelper helper;

        switch (msg.level)
        {
            case spdlog::level::level_enum::trace:
                helper.level = "trace";
                helper.color = glm::vec4(0.83f, 0.83f, 0.83f, 1.0f);
                ss << "[" << times << "] [" << msg.logger_name.data() << "] [" << helper.level << "] " << msg.payload.data();
                helper.str = ss.str();
                if (m_InfoData.m_TraceLogInfos.size() == m_MaxInfos)
                {
                    m_InfoData.m_TraceLogInfos.pop();
                }
                m_InfoData.m_TraceLogInfos.push(helper);
                break;

            case spdlog::level::level_enum::info:
                helper.level = "info";
                helper.color = glm::vec4(0.574f, 0.829f, 1.0f, 1.0f);
                ss << "[" << times << "] [" << msg.logger_name.data() << "] [" << helper.level << "] " << msg.payload.data();
                helper.str = ss.str();
                if (m_InfoData.m_InfoLogInfos.size() == m_MaxInfos)
                {
                    m_InfoData.m_InfoLogInfos.pop();
                }
                m_InfoData.m_InfoLogInfos.push(helper);
                break;

            case spdlog::level::level_enum::warn:
                helper.level = "warn";
                helper.color = glm::vec4(0.974f, 0.896f, 0.39f, 1.0f);
                ss << "[" << times << "] [" << msg.logger_name.data() << "] [" << helper.level << "] " << msg.payload.data();
                helper.str = ss.str();
                if (m_InfoData.m_WarnLogInfos.size() == m_MaxInfos)
                {
                    m_InfoData.m_WarnLogInfos.pop();
                }
                m_InfoData.m_WarnLogInfos.push(helper);
                break;

            case spdlog::level::level_enum::err:
                helper.level = "error";
                helper.color = glm::vec4(1.0f, 0.641f, 0.59f, 1.0f);
                ss << "[" << times << "] [" << msg.logger_name.data() << "] [" << helper.level << "] " << msg.payload.data();
                helper.str = ss.str();
                if (m_InfoData.m_ErrorLogInfos.size() == m_MaxInfos)
                {
                    m_InfoData.m_ErrorLogInfos.pop();
                }
                m_InfoData.m_ErrorLogInfos.push(helper);
                break;

            case spdlog::level::level_enum::critical:
                helper.level = "critical";
                helper.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
                ss << "[" << times << "] [" << msg.logger_name.data() << "] [" << helper.level << "] " << msg.payload.data();
                helper.str = ss.str();
                if (m_InfoData.m_CriticalLogInfos.size() == m_MaxInfos)
                {
                    m_InfoData.m_CriticalLogInfos.pop();
                }
                m_InfoData.m_CriticalLogInfos.push(helper);
                break;

            default:
                break;
        }
    }
}