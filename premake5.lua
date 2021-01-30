workspace "Mandas"
	architecture "x64"

	startproject "Mandas-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Mandas/vendor/GLFW/include"
IncludeDir["Glad"] = "Mandas/vendor/Glad/include"
IncludeDir["ImGui"] = "Mandas/vendor/ImGui"
IncludeDir["glm"] = "Mandas/vendor/glm"
IncludeDir["stb_image"] = "Mandas/vendor/stb_image"

include "Mandas/vendor/GLFW"
include "Mandas/vendor/Glad"
include "Mandas/vendor/ImGui"

group "Dependencies"
	include "Mandas/vendor/GLFW"
	include "Mandas/vendor/Glad"
	include "Mandas/vendor/ImGui"

group ""

project "Mandas"
	location "Mandas"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mdpch.h"
	pchsource "Mandas/src/mdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"MD_BUILD_DLL",
			"_CONSOLE",
			"GLFW_INCLUDE_NONE"
		}

		-- postbuildcommands
		-- {
		-- 	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		-- }

	filter "configurations:Debug"
		defines "MD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MD_DIST"
		runtime "Release"
		optimize "on"

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
		"Mandas/vendor/spdlog/include",
		"Mandas/src",
		"Mandas/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mandas"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"_CONSOLE"
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MD_DIST"
		runtime "Release"
		optimize "on"

project "Mandas-Editor"
	location "Mandas-Editor"
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
		"Mandas/vendor/spdlog/include",
		"Mandas/src",
		"Mandas/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mandas"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"_CONSOLE"
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MD_DIST"
		runtime "Release"
		optimize "on"
