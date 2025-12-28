#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include <array>

namespace PlayGround::Vulkan {

    class Infrastructure;

    enum class EInfrastructure : uint8_t
    {
        Instance = 0,
        Functions,
        DebugUtilsObject,
        Surface,
        PhysicalDevice,
        Device,

        GraphicQueue,
        PresentQueue,
        ComputeQueue,
        TransferQueue,
        VideoEncodeQueue,

        GraphicThreadQueue,
        ComputeThreadQueue,

        MemoryAllocator,
        SwapChain,
        
        GraphicImageSemaphore,
        GraphicQueueSemaphore,
        GraphicFence,
        
        ComputeQueueSemaphore,
        ComputeFence,

        VideoEncodeQueueSemaphore,
        VideoEncodeFence,

        GraphicCommandPool,
        GraphicCommandBuffer,

        ComputeCommandPool,
        ComputeCommandBuffer,

        VideoEncodeCommandPool,
        VideoEncodeCommandBuffer,

        DescriptorPool,

        MAX
    };

    template<typename T_, EInfrastructure E_>
	struct InfrastructureClass
	{
		using T = T_;
        static constexpr EInfrastructure E = E_;
	};

    class Context : NonCopyable
    {
    public:

        Context() = default;

        ~Context() override = default;

        template<typename I, typename... Args>
        void Registry(Args&&... args);

        template<typename I>
        void UnRegistry();

        template<typename I>
        I::T* Get();

        template<typename I>
        bool Has() const;

    private:

        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::MAX)> m_Infrastructures;
    };

    template<typename I, typename... Args>
    void Context::Registry(Args&&... args)
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure already registered.")
        }

        m_Infrastructures[position] = CreateSP<typename I::T>(*this, I::E, std::forward<Args>(args)...);
    }

    template <typename I>
    void Context::UnRegistry()
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure is not registered, can not be unregister")
            return;
        }

        m_Infrastructures[position].reset();
        m_Infrastructures[position] = nullptr;
    }

    template<typename I>
    I::T* Context::Get()
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            CORE_ERROR("Vulkan Infrastructure is not registered, can not be got")
            return nullptr;
        }

        return static_cast<I::T*>(m_Infrastructures[position].get());
    }

    template<typename I>
    bool Context::Has() const
    {
        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }

}