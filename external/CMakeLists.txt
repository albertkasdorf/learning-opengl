include(FetchContent)

add_subdirectory(fmt)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)

FetchContent_MakeAvailable(
    glfw glm fmt spdlog
)
