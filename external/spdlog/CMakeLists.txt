FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        7e635fca68d014934b4af8a1cf874f63989352b7 # Tag v1.12.0
)

#set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "")
set(SPDLOG_FMT_EXTERNAL_HO ON CACHE INTERNAL "")

# project(spdlog VERSION ${SPDLOG_VERSION} LANGUAGES CXX)
# add_library(spdlog::spdlog ALIAS spdlog)
