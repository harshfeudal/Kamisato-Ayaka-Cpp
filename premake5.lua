-- Workspace setup --
workspace "Kamisato Ayaka"
    architecture "x86_64"
    configurations { "Release" }

-- Project setup --
project "Kamisato Ayaka"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	staticruntime "off"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files
    {
        "**.cpp",
        "commands/**.h",
        "commands/**.cpp"
    }

    includedirs
	{
		"../include/include-dpp-10.0"
	}