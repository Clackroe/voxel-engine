project "voxel-game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.cpp",
        "include/**.h",
        "include/**.hpp",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
        "assets/*"

    }

    includedirs{
        "include",
        "vendor/GLAD/include",
        "vendor/GLFW/include",
        "vendor/GLM",
        "vendor/stb_image",
        "vendor/JSON/include",
        "vendor/NOISE"
    }

    links{
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }


    filter "system:windows"
        systemversion "latest"

        defines
        {
            "VOXEL_PLATFORM_WINDOWS"
        }
    filter "configurations:Debug"
        buildoptions "/MTd"`
        defines "VOXEL_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        buildoptions "/MT"
        defines "VOXEL_RELEASE"
        runtime "Release"
        optimize "on"
