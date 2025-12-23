#include "Core/Core.h"
#include "Log.h"
#include "LogImpl.h"

namespace PlayGround {

    static std::shared_ptr<Log> s_Log = nullptr;

    std::shared_ptr<Log> Log::Get()
    {
        if(!s_Log)
        {
            s_Log = std::make_shared<LogImpl>();
        }

        return s_Log;
    }

    void Log::Reset()
    {
        s_Log.reset();
    }

}