workspace "Blueberry-Engine"
	architecture "x64"

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

include "Blueberry-Engine/vendor/GLFW"
include "Blueberry-Engine/vendor/GLAD"
include "Blueberry-Engine/vendor/imgui"

project "Blueberry-Engine"
	location "Blueberry-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bepch.h"
	pchsource "%{prj.name}/src/bepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
	"%{prj.name}/vendor/spdlog/include",
	"%{prj.name}/src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLAD}",
	"%{IncludeDir.ImGui}"
	}
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE"
		}

	postbuildcommands{
	("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandboxTesting")
	}
	filter "configurations:Debug"
		defines "BE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "BE_DIST"
		buildoptions "/MD"
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
	"Blueberry-Engine/src"
	}

	links
	{
	"Blueberry-Engine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines{
			"BE_PLATFORM_WINDOWS",
			"_WINDLL"
		}
	
	filter "configurations:Debug"
		defines "BE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "BE_DIST"
		buildoptions "/MD"
		optimize "On"