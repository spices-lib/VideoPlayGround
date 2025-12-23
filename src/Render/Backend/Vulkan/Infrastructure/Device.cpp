#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "ThreadQueue.h"
#include <unordered_map>
#include "DebugUtils.h"

namespace PlayGround::Vulkan {

    Device::Device(Context& context)
        : Infrastructure(context)
    {
        Create();
    }

    void Device::Create()
    {
		const auto physicalDevice = m_Context.Get<PhysicalDevice>();
		const auto& queueFaimilies = physicalDevice->GetQueueFamilies();

		std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::vector<VkQueue>>> queueFamilies;

		queueFamilies[queueFaimilies.graphic .value()][0] = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.present .value()][1] = std::vector<VkQueue>(1, VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.compute .value()][2] = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.transfer.value()][3] = std::vector<VkQueue>(1, VK_NULL_HANDLE);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::vector<std::shared_ptr<std::vector<float>>> QueuePriorities;
		for (auto& [family, idItems] : queueFamilies)
		{
			uint32_t count = 0;
			for (auto& [id, queues] : idItems)
			{
				count += queues.size();
			}

			std::shared_ptr<std::vector<float>> queuePriority = std::make_shared<std::vector<float>>(count, 1.0f);

			VkDeviceQueueCreateInfo                               queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = family;
			queueCreateInfo.queueCount = count;
			queueCreateInfo.pQueuePriorities = queuePriority->data();

			QueuePriorities.push_back(queuePriority);
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures2                                 deviceFeatures{};
		deviceFeatures.sType                                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                    = nullptr;

		vkGetPhysicalDeviceFeatures2(physicalDevice->Handle(), &deviceFeatures);

        VkDeviceCreateInfo                                        createInfo{};
		createInfo.sType                                        = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos                            = queueCreateInfos.data();
		createInfo.queueCreateInfoCount                         = queueCreateInfos.size();
		createInfo.pEnabledFeatures                             = VK_NULL_HANDLE;
		createInfo.enabledExtensionCount                        = physicalDevice->GetExtensionRequirements().size();
		createInfo.ppEnabledExtensionNames                      = physicalDevice->GetExtensionRequirements().data();
		createInfo.enabledLayerCount                            = 0;
		createInfo.pNext                                        = &deviceFeatures;

		VK_CHECK(vkCreateDevice(physicalDevice->Handle(), &createInfo, nullptr, &m_Handle));
		DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_DEVICE, (uint64_t)m_Handle, physicalDevice->GetProperties().deviceName)

		for (auto& [family, idItems] : queueFamilies)
		{
			int index = 0;
			for (auto& [id, items] : idItems)
			{
				for (size_t i = 0; i < items.size(); i++)
				{
					vkGetDeviceQueue(m_Handle, family, index, &items[i]);
					index++;
				}
			}
		}

		

#if 0 // Use One Queue for all commands. This method with higher fps.

		auto graphic  = queueFamilies[queueFaimilies.graphic.value()][0][0];
		auto present  = queueFamilies[queueFaimilies.graphic.value()][0][0];
		auto compute  = queueFamilies[queueFaimilies.graphic.value()][0][0];
		auto transfer = queueFamilies[queueFaimilies.graphic.value()][0][0];

#else // Split Commands to different Queues.

		auto graphic  = queueFamilies[queueFaimilies.graphic .value()][0][0];
		auto present  = queueFamilies[queueFaimilies.present .value()][0][0];
		auto compute  = queueFamilies[queueFaimilies.compute .value()][2][0];
		auto transfer = queueFamilies[queueFaimilies.transfer.value()][3][0];

#endif

		m_Context.Registry<Queue>();
		m_Context.Get<Queue>()->Init(graphic, present, compute, transfer);

		m_Context.Registry<ThreadQueue>();

		for (int i = 0; i < NThreadQueue; i++)
		{
			m_Context.Get<ThreadQueue>()->AddGraphic(queueFamilies[queueFaimilies.graphic.value()][0][i + 1]);
			m_Context.Get<ThreadQueue>()->AddCompute(queueFamilies[queueFaimilies.compute.value()][2][i + 1]);
		}
    }

}