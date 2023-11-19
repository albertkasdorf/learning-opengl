FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG        09155eaa2f9270dc4ed1fa13e2b4b2613e6e4851 # Tag v1.3
)

# project(zlib C)
# add_library(zlib SHARED ...)
# add_library(zlibstatic STATIC ...)