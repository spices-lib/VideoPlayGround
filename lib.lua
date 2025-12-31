IncludeDir                                = {}
IncludeDir["GLFW"]                        = "%{wks.location}/vendor/GLFW/include"
IncludeDir["VulkanSDK"]                   = "C:/VulkanSDK/1.4.321.1/Include"
IncludeDir["glm"]                         = "%{IncludeDir.VulkanSDK}/glm"
IncludeDir["ImGui"]                       = "%{wks.location}/vendor/imgui"
IncludeDir["VulkanMemoryAllocator"]       = "%{IncludeDir.VulkanSDK}/vma"
IncludeDir["spdlog"]                      = "%{wks.location}/vendor/spdlog/include"
IncludeDir["entt"]                        = "%{wks.location}/vendor/entt/include"
IncludeDir["ffmpeg"]                      = "%{wks.location}/vendor/ffmpeg/win64/include"

LibraryDir                                = {}
LibraryDir["VulkanSDK"]                   = "C:/VulkanSDK/1.4.321.1/Lib"
LibraryDir["ffmpeg"]                      = "%{IncludeDir.ffmpeg}/../lib"
LibraryDir["ffmpeg_dll"]                  = "%{IncludeDir.ffmpeg}/../bin"

Library                                   = {}
Library["VulkanSDK"]                      = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["avcodec"]                        = "%{LibraryDir.ffmpeg}/avcodec.lib"
Library["avdevice"]                       = "%{LibraryDir.ffmpeg}/avdevice.lib"
Library["avfilter"]                       = "%{LibraryDir.ffmpeg}/avfilter.lib"
Library["avformat"]                       = "%{LibraryDir.ffmpeg}/avformat.lib"
Library["avutil"]                         = "%{LibraryDir.ffmpeg}/avutil.lib"
Library["swresample"]                     = "%{LibraryDir.ffmpeg}/swresample.lib"
Library["swscale"]                        = "%{LibraryDir.ffmpeg}/swscale.lib"