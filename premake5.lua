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

project "Neva"
	location "Neva"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Neva/src",
		"Neva/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS",
			"NV_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NV_DIST"
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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NV_DIST"
		optimize "On"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/utf-8"

	filter {"system:windows", "configurations:Dist"}
		buildoptions "/utf-8"