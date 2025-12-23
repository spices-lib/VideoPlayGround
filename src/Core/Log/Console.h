#pragma once
#include "Core/Core.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <glm/glm.hpp>
#include <queue>

namespace PlayGround {

    struct InfoLevelHelper
    {
        std::string str;
        std::string level;
        glm::vec4 color;
    };

    struct InfoData
    {
        std::queue<InfoLevelHelper> m_TraceLogInfos;   
        std::queue<InfoLevelHelper> m_InfoLogInfos;    
        std::queue<InfoLevelHelper> m_WarnLogInfos;    
        std::queue<InfoLevelHelper> m_ErrorLogInfos;   
        std::queue<InfoLevelHelper> m_CriticalLogInfos;

        void Clear()
        {
            std::queue<InfoLevelHelper>().swap(m_TraceLogInfos);
            std::queue<InfoLevelHelper>().swap(m_InfoLogInfos);
            std::queue<InfoLevelHelper>().swap(m_WarnLogInfos);
            std::queue<InfoLevelHelper>().swap(m_ErrorLogInfos);
            std::queue<InfoLevelHelper>().swap(m_CriticalLogInfos);
        }
    };

    class Console : public spdlog::sinks::base_sink<std::mutex>
    {
    public:

        static std::shared_ptr<Console> Registry(const std::string& name);

    public:

        Console(uint32_t maxInfos = 50);
        ~Console() override = default;

        const InfoData& GetInfos() const { return m_InfoData; }
        void Clear();
        void Push(const std::string& cmd);

    protected:

        void sink_it_(const spdlog::details::log_msg& msg) override;
        void flush_() override { Clear(); }

    protected:

        uint32_t m_MaxInfos;
        InfoData m_InfoData;
    };
}