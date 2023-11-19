FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        7482de6071d21db77a7236155da44c172a7f6c9e # Tag 3.3.8
)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

# project(GLFW VERSION 3.4.0 LANGUAGES C)
# GLFW_LIBRARY_TYPE = static or shared
# add_library(glfw ${GLFW_LIBRARY_TYPE} ...)