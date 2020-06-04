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
IncludeDir["stb_image"] = "Blueberry-Engine/vendor/stb_image"

group "Dependencies"
include "Blueberry-Engine/vendor/GLFW"
include "Blueberry-Engine/vendor/GLAD"
include "Blueberry-Engine/vendor/imgui"
group ""

project "Blueberry-Engine"
	location "Blueberry-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bepch.h"
	pchsource "%{prj.name}/src/bepch.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
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
	"%{IncludeDir.glm}",
	"%{IncludeDir.stb_image}"
	}
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	
	filter "system:windows"
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "on"

project "SandboxTesting"
	location "SandboxTesting"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"

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
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"_WINDLL"
		}
	
	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "on"