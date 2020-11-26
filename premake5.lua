workspace "Mandas"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Mandas"
	location "Mandas"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mdpch.h"
	pchsource "Mandas/src/mdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"MD_BUILD_DLL",
			"_CONSOLE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MD_DIST"
		optimize "On"

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
		"Mandas/vendor/spdlog/include",
		"Mandas/src"
	}

	links
	{
		"Mandas"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"_CONSOLE"
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MD_DIST"
		optimize "On"
