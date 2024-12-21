## NOTE: This was the very first graphics project AND my very first C/C++ project. This is kept public only as a reminder to what originally made me passionate about graphics and game engines.

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
- This project uses [premake5](https://premake.github.io/download) check their docs for more information
- Use the bat file (windows), and the bash file (Linux) to generate the project files.
### Generate help message
```CMD
   ./build.bat
```
```bash
   ./build.sh
```
![image](https://github.com/Clackroe/voxel-engine/assets/65436489/f905285b-aea9-42f2-b8f2-f25864d82976)

### Generate files
```CMD
   ./build.bat vs2022
```
```bash
   ./build.sh gmake2
```

## Build with whatever system you are using! Have fun!
