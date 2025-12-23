#pragma once
#include "Core/Core.h"

namespace PlayGround {

    class UUID
    {
    public:

        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const { return m_UUID; }

        std::string ToString() const;

    private:

        uint64_t m_UUID;
    };

}

namespace std {

    template<>
    struct hash<PlayGround::UUID>
    {
        std::size_t operator()(const PlayGround::UUID& uuid) const noexcept
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}