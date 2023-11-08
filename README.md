

# Getting Started

## To Clone With Submodules [REQUIRED]
```bash
  git clone --recurse-submodules git@github.com:Clackroe/voxel-engine.git
```

## Pull latest dependency changes [MAYBE REQUIRED]
```bash
  git submodule update --remote
```

## Build [REQUIRED]
### Note: Currently include paths may be bugged on Linux. You may need to change them when building
- make sure you have [premake5](https://premake.github.io/download) installed
- Use premake for however you will be building (Visual studio / make examples below)
```bash
  premake5 [vs2022 | gmake2]
```

## Build with whatever system you are using! Have fun!
