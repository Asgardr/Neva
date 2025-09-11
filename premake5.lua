workspace "Neva"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Neva/vendor/GLFW/include"
IncludeDir["Glad"] = "Neva/vendor/Glad/include"
IncludeDir["ImGui"] = "Neva/vendor/imgui"

include "Neva/vendor/GLFW"
include "Neva/vendor/Glad"
include "Neva/vendor/imgui"

project "Neva"
	location "Neva"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nvpch.h"
	pchsource "Neva/src/nvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Neva/src",
		"Neva/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib";
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS",
			"NV_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NV_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NV_DIST"
		runtime "Release"
		optimize "On"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Dist"}
		buildoptions "/utf-8"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Neva/vendor/spdlog/include",
		"Neva/src"
	}

	links
	{
		"Neva"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NV_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NV_DIST"
		runtime "Release"
		optimize "On"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Dist"}
		buildoptions "/utf-8"