cmake_minimum_required(VERSION 3.16)

project(scotty3d VERSION 0.1
				 DESCRIPTION "Scotty3d Future: 15-462 CMU"
				 LANGUAGES CXX)

set(SOURCES_SCOTTY3D_LIB
					"src/lib/bbox.h"
					"src/lib/camera.h"
					"src/lib/line.h"
					"src/lib/log.h"
					"src/lib/mat4.h"
					"src/lib/mathutils.h"
					"src/lib/plane.h"
					"src/lib/quat.h"
					"src/lib/vec2.h"
					"src/lib/vec3.h"
					"src/lib/vec4.h")
set(SOURCES_SCOTTY3D_SCENE
					"src/scene/halfedge.cpp"
					"src/scene/halfedge.h"
					"src/scene/render.cpp"
					"src/scene/render.h"
					"src/scene/scene.cpp"
					"src/scene/scene.h"
					"src/scene/util.cpp"
					"src/scene/util.h")
set(SOURCES_SCOTTY3D_PLATFORM
					"src/platform/gl.cpp"
					"src/platform/gl.h"
					"src/platform/font.h"
					"src/platform/platform.cpp"
					"src/platform/platform.h")

set(SOURCES_SCOTTY3D ${SOURCES_SCOTTY3D_LIB}
					 ${SOURCES_SCOTTY3D_SCENE}
					 ${SOURCES_SCOTTY3D_PLATFORM}
				     "src/app.cpp"
				     "src/app.h"
				     "src/gui.cpp"
				     "src/gui.h"
				     "src/undo.cpp"
				     "src/undo.h"
				     "src/main.cpp")

source_group(lib FILES ${SOURCES_SCOTTY3D_LIB})
source_group(scene FILES ${SOURCES_SCOTTY3D_SCENE})
source_group(platform FILES ${SOURCES_SCOTTY3D_PLATFORM})

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

# Set linux convenience var
if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

set(LOCAL_INCLUDE_DIRS "${scotty3d_SOURCE_DIR}/deps/")

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation -framework ApplicationServices -framework Foundation -framework AppKit")
endif()

find_package(PkgConfig REQUIRED)

# find assimp
pkg_check_modules(ASSIMP REQUIRED IMPORTED_TARGET assimp)
include_directories(${ASSIMP_INCLUDE_DIRS})
add_definitions(${ASSIMP_CFLAGS_OTHER})

# find gtk+3
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# find sdl2
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
include_directories(${SDL2_INCLUDEDIR} ${SDL2_INCLUDE_DIRS})
add_definitions(${SDL2_CFLAGS_OTHER})

# local includes
include_directories(${LOCAL_INCLUDE_DIRS})

add_subdirectory("deps/imgui/")
add_subdirectory("deps/glad/")
add_subdirectory("deps/nfd/")

# define executable
add_executable(scotty3d ${SOURCES_SCOTTY3D})

set_target_properties(scotty3d PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )

target_include_directories(scotty3d PRIVATE "src/" "src/lib/")

# link found libraries
target_link_directories(scotty3d PUBLIC ${GTK3_LIBRARY_DIRS})
target_link_directories(scotty3d PUBLIC ${SDL2_LIBRARY_DIRS})
target_link_directories(scotty3d PUBLIC ${ASSIMP_LIBRARY_DIRS})

target_link_libraries(scotty3d ${SDL2_LIBRARIES})
target_link_libraries(scotty3d ${ASSIMP_LIBRARIES})
target_link_libraries(scotty3d ${GTK3_LIBRARIES})
target_link_libraries(scotty3d nfd)
target_link_libraries(scotty3d imgui)
target_link_libraries(scotty3d glad)