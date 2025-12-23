#pragma once
#include "Core/Core.h"
#include "Component.h"

namespace PlayGround {

    class TagComponent : public Component
    {
    public:

        TagComponent() = default;

        TagComponent(const std::string& tag) : m_Tags(tag) {}

        ~TagComponent() override = default;

        void Rename(const std::string& tag);

        const std::string& GetTag() { return m_Tags; }

    private:

        std::string m_Tags;
    };
} 