cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE DLL
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/zar/*.cpp 
         ${CMAKE_CURRENT_SOURCE_DIR}/zar/*.h)


option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

add_subdirectory(vendor/glew-cmake)

add_subdirectory(vendor/spdlog)

include_directories(
                    vendor/assimp/include/ 
                    vendor/glew-cmake/include/ 
                    vendor/glfw/include/ 
                    vendor/glm/ 
                    vendor/stb/ 
                    vendor/spdlog/include/ 
                   )

add_library(zar SHARED ${DLL})

target_compile_definitions(zar PUBLIC FX_PLATFORM_WINDOWS)
target_compile_definitions(zar PUBLIC FX_BUILD_DLL)

target_link_libraries(zar PUBLIC assimp glfw libglew_shared spdlog)

set_target_properties(assimp PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_target_properties(libglew_shared PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_target_properties(glfw PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_target_properties(spdlog PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

target_precompile_headers(zar PRIVATE 
"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/zar/pch.h>")
