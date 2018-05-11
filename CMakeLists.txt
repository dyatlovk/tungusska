# CMake entry point
cmake_minimum_required(VERSION 2.6)
project(Tungusska)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

set(Boost_USE_MULTITHREADED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(Lua51 REQUIRED)

# Compile external dependencies
#add_subdirectory(external)

include_directories(
        .
        ${ASSIMP_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${LUA_INCLUDE_DIR}
)

set(
        ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLEW_LIBRARY}
        ${ASSIMP_LIBRARY}
        ${Boost_LIBRARIES}
        SDL2
        SDL2_image
        assimp
        lua5.1
        ${CMAKE_THREAD_LIBS_INIT}
)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -D_CRT_SECURE_NO_WARNINGS
        -DBOOST_LOG_DYN_LINK
        # -Wabi-tag
        # debug
        # -O3
        # -D_GLIBCXX_DEBUG
        # -D_GLIBCXX_DEBUG_PEDANTIC
        # -g
        # -ggdb
)

# App
add_executable(
        tungusska
        src/CVar.h
        src/game.cpp
        src/game.h
        src/main.cpp
        # Game states
        src/GameState.h
        src/MenuState.cpp
        src/MenuState.h
        src/PlayState.cpp
        src/PlayState.cpp
        src/PlayState.h
        src/PauseState.cpp
        src/PauseState.h
        # imgui
        src/libs/imgui/imgui.h
        src/libs/imgui/imgui.cpp
        src/libs/imgui/imconfig.h
        src/libs/imgui/imgui_draw.cpp
        src/libs/imgui/stb_rect_pack.h
        src/libs/imgui/stb_textedit.h
        # src/libs/imgui/stb_truetype.h
        src/libs/imgui/imgui_impl_sdl.h
        src/libs/imgui/imgui_impl_sdl.cpp
        src/libs/imgui/imgui_demo.cpp
        # SOL2
        # src/external/sol2/single/sol/sol.hpp

        src/ui/HUD.h
        src/ui/HUD.cpp
        src/Camera.cpp
        src/Camera.h
        src/Log.cpp
        src/Log.h
        src/Mesh.h
        src/Mesh.cpp
        src/utils/gl_helpers.cpp
        src/utils/gl_helpers.h
        src/Scene.h
        src/Scene.cpp
        src/utils/Watcher.h
        src/utils/Watcher.cpp
        src/utils/sys.h
        # src/utils/Config.cpp
        # src/utils/Config.h
        )
target_link_libraries(tungusska ${ALL_LIBS})

file(MAKE_DIRECTORY "cmake-build-debug")

add_custom_command(
        TARGET tungusska POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "./tungusska"
        "${CMAKE_CURRENT_SOURCE_DIR}/build/bin/"
)
