workspace "LeviathanDX"
	configurations 
	{
		"Debug",
		"Release"
	}
	architecture "x86_64"
	
	
outputdir = "%{prj.name}/%{cfg.buildcfg}"
IncludeDir = {}
IncludeDir["Leviathan"] = "Leviathan/src"



group "Dependencies"
group ""

project "LeviathanDX"
	location "LeviathanDX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"
	toolset "msc-v142"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")
	
	files 
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/include"
	}
	
	defines
	{
		"WIN32_LEAN_AND_MEAN"
	}
	
	libdirs {"%{prj.name}/external/libs/%{cfg.architecture}"}
	links 
	{
	}
	
	filter "configurations:Debug"
		defines "LV_DEBUG"
		symbols "On"
		optimize "Off"
	filter "configurations:Release"
		defines {"LV_RELEASE", "NDEBUG"}
		symbols "Off"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")
	
	files 
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/external/include",
		"LeviathanDX/include",
		"LeviathanDX/external/include",
	}
	
	defines
	{
		"WIN32_LEAN_AND_MEAN"
	}
	
	links 
	{
		"LeviathanDX"
	}
	
	filter "configurations:Debug"
		defines "LV_DEBUG"
		symbols "On"
		optimize "Off"
	filter "configurations:Release"
		defines "LV_RELEASE"
		symbols "Off"
		optimize "On"
	