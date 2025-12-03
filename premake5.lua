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
IncludeDir["glm"] = "Neva/vendor/glm"
IncludeDir["stb_image"] = "Neva/vendor/stb_image"

group "Dependencies"
	include "Neva/vendor/GLFW"
	include "Neva/vendor/Glad"
	include "Neva/vendor/imgui"
group ""

project "Neva"
	location "Neva"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nvpch.h"
	pchsource "Neva/src/nvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Neva/src",
		"Neva/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS",
			"NV_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NV_DIST"
		runtime "Release"
		optimize "on"

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
	cppdialect "C++17"
	staticruntime "on"

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
		"Neva/src",
		"Neva/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Neva"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NV_DIST"
		runtime "Release"
		optimize "on"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Dist"}
		buildoptions "/utf-8"