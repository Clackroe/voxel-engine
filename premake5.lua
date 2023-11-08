workspace "voxel-engine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    startproject "voxel-game"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "voxel-game"
include "voxel-game/vendor/GLFW"
include "voxel-game/vendor/GLAD"

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin*")
        print("Removing intermediate binaries")
        os.rmdir("./bin-intDebug-windows-x86_64")
        os.rmdir("./bin-intDebug-linux-x86_64")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}
