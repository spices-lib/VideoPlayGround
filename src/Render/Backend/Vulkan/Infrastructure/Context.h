#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include <array>

namespace PlayGround::Vulkan {

    class Infrastructure;

    enum class EInfrastructure : uint8_t
    {
        Instance,
        Functions,
        DebugUtilsObject,
        Surface,
        PhysicalDevice,
        Device,
        Queue,
        ThreadQueue,
        MemoryAllocator,
        SwapChain,
        SwapChainImage,
        GraphicCommandPool,
        GraphicCommandBuffer,
        GraphicImageSemaphore,
        GraphicQueueSemaphore,
        GraphicFence,


        DescriptorPool,

        MAX
    };

    class Context : NonCopyable
    {
    public:

        Context() = default;

        ~Context() override = default;

        template<typename T, typename... Args>
        void Registry(Args&&... args);

        template<typename T>
        void UnRegistry();

        template<typename T>
        T* Get();

    private:

        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::MAX)> m_Infrastructures;
    };

    template<typename T, typename... Args>
    void Context::Registry(Args&&... args)
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure already registried.")
        }

        m_Infrastructures[position] = CreateSP<T>(*this, std::forward<Args>(args)...);
    }

    template <typename T>
    void Context::UnRegistry()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure is unregistry.")
            return;
        }

        m_Infrastructures[position].reset();
        m_Infrastructures[position] = nullptr;
    }

    template<typename T>
    T* Context::Get()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure is unregistry.")
            return nullptr;
        }

        return static_cast<T*>(m_Infrastructures[position].get());
    }

}