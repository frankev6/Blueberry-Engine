workspace "Blueberry-Engine"
	architecture "x64"
	startproject "SandboxTesting"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Blueberry-Engine/vendor/GLFW/include"
IncludeDir["GLAD"] = "Blueberry-Engine/vendor/GLAD/include"
IncludeDir["ImGui"] = "Blueberry-Engine/vendor/imgui"
IncludeDir["glm"] = "Blueberry-Engine/vendor/glm"

group "Dependencies"
include "Blueberry-Engine/vendor/GLFW"
include "Blueberry-Engine/vendor/GLAD"
include "Blueberry-Engine/vendor/imgui"
group ""

project "Blueberry-Engine"
	location "Blueberry-Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bepch.h"
	pchsource "%{prj.name}/src/bepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/glm/glm/**.hpp"
	}

	includedirs
	{
	"%{prj.name}/vendor/spdlog/include",
	"%{prj.name}/src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLAD}",
	"%{IncludeDir.ImGui}",
	"%{IncludeDir.glm}"
	}
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE",
		}

	postbuildcommands{
	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" ..outputdir.. "/SandboxTesting/\"")
	}
	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "On"

project "SandboxTesting"
	location "SandboxTesting"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
	"Blueberry-Engine/vendor/spdlog/include",
	"Blueberry-Engine/src",
	"Blueberry-Engine/vendor",
	"%{IncludeDir.glm}"
	}

	links
	{
	"Blueberry-Engine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"_WINDLL"
		}
	
	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "On"