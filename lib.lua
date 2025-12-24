IncludeDir                                = {}
IncludeDir["GLFW"]                        = "%{wks.location}/vendor/GLFW/include"
IncludeDir["VulkanSDK"]                   = "C:/VulkanSDK/1.4.321.1/Include"
IncludeDir["glm"]                         = "%{IncludeDir.VulkanSDK}/glm"
IncludeDir["ImGui"]                       = "%{wks.location}/vendor/imgui"
IncludeDir["VulkanMemoryAllocator"]       = "%{IncludeDir.VulkanSDK}/vma"
IncludeDir["spdlog"]                      = "%{wks.location}/vendor/spdlog/include"
IncludeDir["entt"]                        = "%{wks.location}/vendor/entt/include"

LibraryDir                                = {}
LibraryDir["VulkanSDK"]                   = "C:/VulkanSDK/1.4.321.1/Lib"

Library                                   = {}
Library["VulkanSDK"]                      = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"