VENDOR_INCLUDES = { 
	"vendor/glm", 
	"vendor/SDL2-2.0.3/include", 
	"vendor/bgfx/include", 
	"vendor/bx/include" 
}

project "bgfx"
	kind "StaticLib"
	language "C++"
	targetdir "lib/%{cfg.buildcfg}"

	includedirs { "vendor/bgfx/include", "vendor/bx/include", "vendor/bgfx/3rdparty/khronos" }
	files { "vendor/bgfx/include/*.h", "vendor/bgfx/src/amalgamated.cpp" }
	defines { "BGFX_CONFIG_RENDERER_DIRECT3D11=1" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	configuration { "gmake" }
		buildoptions { "-std=c++11" }

	configuration "vs*"
		includedirs { "vendor/bx/include/compat/msvc" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

project "Vespertine"
	kind "StaticLib"
	language "C++"
	targetdir "lib/%{cfg.buildcfg}"

	links { "bgfx" }
	includedirs(VENDOR_INCLUDES)
	includedirs { "include/" }
	files { "include/**.hpp", "src/**.cpp" }
	flags { "NoExceptions", "NoRTTI", "FatalWarnings" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	configuration { "gmake" }
		buildoptions { "-std=c++11" }