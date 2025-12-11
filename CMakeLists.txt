# Set minimum CMake version.
cmake_minimum_required(VERSION 3.16)

# Define project.
project(notepad VERSION 1.0 LANGUAGES CXX)

# Set C++ standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Add executable and link files.
add_executable(notepad 
    src/main.cpp
)

# Include directories.
target_include_directories(notepad PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# Add SFML
add_subdirectory(vendors/sfml)

# Tell ImGui-SFML where to find ImGui.
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendors/imgui CACHE PATH "")

# Prevent ImGui-SFML from searching and linking SFML itself since we are vendoring it.
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "")

# Add ImGui-SFML.
add_subdirectory(vendors/imgui-sfml)

# Link libraries.
target_link_libraries(notepad PRIVATE
    ImGui-SFML::ImGui-SFML
    sfml-graphics
    sfml-window
    sfml-system
)

# macOS OpenGL framework.
if (APPLE)
    target_link_libraries(notepad PRIVATE "-framework OpenGL")
endif()

# Precompiled header
target_precompile_headers(notepad PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/include/pch.hpp>"
)