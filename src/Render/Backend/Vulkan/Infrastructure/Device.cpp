#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "ThreadQueue.h"
#include <unordered_map>
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

    void Device::Create()
    {
		const auto physicalDevice = GetContext().Get<IPhysicalDevice>();
		const auto& queueFaimilies = physicalDevice->GetQueueFamilies();

		std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::vector<VkQueue>>> queueFamilies;

		queueFamilies[queueFaimilies.graphic .value()][0]    = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.present .value()][1]    = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.compute .value()][2]    = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.transfer.value()][3]    = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[queueFaimilies.videoEncode.value()][4] = std::vector<VkQueue>(1,                VK_NULL_HANDLE);

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
			queueCreateInfo.sType                               = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex                    = family;
			queueCreateInfo.queueCount                          = count;
			queueCreateInfo.pQueuePriorities                    = queuePriority->data();

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

		m_Device.CreateDevice(physicalDevice->Handle(), &createInfo);
		DEBUGUTILS_SETOBJECTNAME(m_Device, physicalDevice->GetProperties().deviceName)

		for (auto& [family, idItems] : queueFamilies)
		{
			int index = 0;
			for (auto& [id, items] : idItems)
			{
				for (size_t i = 0; i < items.size(); i++)
				{
					items[i] = m_Device.GetDeviceQueue(family, index);
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

		auto graphic     = queueFamilies[queueFaimilies.graphic    .value()][0][0];
		auto present     = queueFamilies[queueFaimilies.present    .value()][0][0];
		auto compute     = queueFamilies[queueFaimilies.compute    .value()][2][0];
		auto transfer    = queueFamilies[queueFaimilies.transfer   .value()][3][0];
		auto videoEncode = queueFamilies[queueFaimilies.videoEncode.value()][4][0];

#endif

		GetContext().Registry<IGraphicQueue>    (graphic);
		GetContext().Registry<IPresentQueue>    (present);
		GetContext().Registry<IComputeQueue>    (compute);
		GetContext().Registry<ITransferQueue>   (transfer);
		GetContext().Registry<IVideoEncodeQueue>(videoEncode);

		/*DEBUGUTILS_SETOBJECTNAME(m_Context.Get<IGraphicQueue>() , "GraphicQueue")
		DEBUGUTILS_SETOBJECTNAME(m_Context.Get<IPresentQueue>() , "PresentQueue")
		DEBUGUTILS_SETOBJECTNAME(m_Context.Get<IComputeQueue>() , "ComputeQueue")
		DEBUGUTILS_SETOBJECTNAME(m_Context.Get<ITransferQueue>(), "TransferQueue")*/

		GetContext().Registry<IGraphicThreadQueue>();
		GetContext().Registry<IComputeThreadQueue>();

		for (int i = 0; i < NThreadQueue; i++)
		{
			GetContext().Get<IGraphicThreadQueue>()->Add(queueFamilies[queueFaimilies.graphic.value()][0][i + 1]);
			GetContext().Get<IComputeThreadQueue>()->Add(queueFamilies[queueFaimilies.compute.value()][2][i + 1]);
		}
    }

}