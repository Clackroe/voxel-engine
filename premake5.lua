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
