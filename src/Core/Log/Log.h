#pragma once
#include "Core/NonCopyable.h"

#include <iostream>
#include <memory.h>

namespace PlayGround {

    class Log : public NonCopyable
    {
    public:
        
        static std::shared_ptr<Log> Get();
        static void Reset();

    public:

        Log() = default;
        ~Log() override = default;

        virtual void CoreTrace   (const std::string& msg) = 0;
        virtual void CoreInfo    (const std::string& msg) = 0;
        virtual void CoreWarn    (const std::string& msg) = 0;
        virtual void CoreError   (const std::string& msg) = 0;
        virtual void CoreCritical(const std::string& msg) = 0;

        virtual void ClientTrace   (const std::string& msg) = 0;
        virtual void ClientInfo    (const std::string& msg) = 0;
        virtual void ClientWarn    (const std::string& msg) = 0;
        virtual void ClientError   (const std::string& msg) = 0;
        virtual void ClientCritical(const std::string& msg) = 0;

        bool IsInitialized() const { return m_IsInitialized; }

    protected:

        bool m_IsInitialized = false;
    };
}

#ifdef PG_DEBUG

// Core log macros
#define CORE_TRACE(...)    { if(auto logPtr = PlayGround::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreTrace      (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define CORE_INFO(...)     { if(auto logPtr = PlayGround::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreInfo       (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define CORE_WARN(...)     { if(auto logPtr = PlayGround::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreWarn       (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define CORE_ERROR(...)    { if(auto logPtr = PlayGround::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreError      (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define CORE_CRITICAL(...) { if(auto logPtr = PlayGround::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreCritical   (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }

#endif // PlayGround_DEBUG

#ifdef PG_RELEASE

// Core log macros
#define CORE_TRACE(...)
#define CORE_INFO(...)
#define CORE_WARN(...)
#define CORE_ERROR(...)
#define CORE_CRITICAL(...)

#endif // PlayGround_RELEASE