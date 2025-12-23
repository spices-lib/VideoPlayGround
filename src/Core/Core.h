#pragma once
#include "Log/Log.h"

#include <forward_list>

namespace PlayGround {

#define ASSERT(expr)                                                                                          \
    {                                                                                                         \
        if (expr) {}                                                                                          \
        else                                                                                                  \
        {                                                                                                     \
            std::stringstream ss;                                                                             \
            ss << "Assert Failed \n    At File: " << __FILE__ << " \n   At Line: " << __LINE__ << "\n   ";    \
            CORE_ERROR(ss.str())                                                                      \
        }                                                                                                     \
    }                                                                                                         \

    template<typename T>
    using SP = std::shared_ptr<T>;

    template<typename T, typename ...Args>
    SP<T> CreateSP(Args&&... args)
    {
        return std::move(std::make_shared<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    using WP = std::weak_ptr<T>;

    template<typename T>
    using UP = std::unique_ptr<T>;

    template<typename T, typename ...Args>
    UP<T> CreateUP(Args&&... args)
    {
        return std::move(std::make_unique<T>(std::forward<Args>(args)...));
    }
}