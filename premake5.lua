workspace "video_playground"
	architecture "x64"
	startproject "playground"

	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "lib.lua"

group "Dependencies"
	include "vendor/GLFW/"
	include "vendor/imgui"
group ""

project "playground"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	flags { "MultiProcessorCompile" }

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
	}

	defines
	{
	}

	includedirs
	{
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.VulkanMemoryAllocator}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"GLFW",
		"%{Library.VulkanSDK}",
		"imgui",
	}

	filter "system:windows"
		systemversion   "latest" 
		editAndContinue "Off"

		defines
		{
			"WIN32_LEAN_AND_MEAN"
		}

		links
		{}

	filter "configurations:Debug"

		defines 
		{
			"PG_DEBUG"
		}

		links
		{
		}

		runtime "Debug"
		symbols "On"

	filter "configurations:Release"

		defines 
		{
			"PG_RELEASE"
		}

		links
		{
		}

		runtime "Release"
		optimize "On"