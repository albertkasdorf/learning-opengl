
set(
    TARGET_NAME learn-opengl
)
add_executable(
    ${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/program.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/program.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderType.hpp
)
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
# Suppress MSVC linker warning "LINK : warning LNK4098: defaultlib 'MSVCRT' conflicts with use of other libs; use /NODEFAULTLIB:library"
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
        LINK_FLAGS "/ignore:4098"
)
endif()
target_compile_features(
    ${TARGET_NAME} PRIVATE cxx_std_17
)
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
        glfw
        glad::glad
        glm::glm
        fmt::fmt
        spdlog::spdlog
)