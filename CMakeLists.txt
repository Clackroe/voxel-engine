cmake_minimum_required(VERSION 3.12.0)
project(voxel-engine VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB MAIN_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "src/**/*.c", "src/**/*.cpp", "src/**/*.h", "src/**/**/*.h", "src/**/**/*.cpp")
# file(GLOB MAIN_SRC CONFIGURE_DEPENDS "src/**.h" "src/**.cpp" "src/**.c" "src/**.hpp")

add_executable(voxel-engine ${MAIN_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

target_link_libraries(voxel-engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(voxel-engine glfw OpenGL::GL)
target_link_libraries(voxel-engine ${OpenCV_LIBS})
