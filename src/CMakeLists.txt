
set(
    TARGET_NAME learn-opengl
)
add_executable(
    ${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferUsagePattern.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/error.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indexBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numberOfComponents.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/program.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/program.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderType.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stateVariables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stateVariables.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexArray.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexAttributeIndex.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBufferElement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBufferLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBufferLayout.hpp
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
target_compile_options(
    ${TARGET_NAME}
    PRIVATE
        #
        # Compiler options listed by category
        # https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170
        # https://github.com/cpp-best-practices/cmake_template/blob/main/cmake/CompilerWarnings.cmake
        #
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)
target_compile_features(
    ${TARGET_NAME} PRIVATE cxx_std_17
)
target_compile_definitions(
    ${TARGET_NAME}
    PRIVATE
        GLAD_GL_IMPLEMENTATION
        GLFW_INCLUDE_NONE
)
#
# Cross Compiling With CMake, https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html
#
if(CMAKE_HOST_WIN32)
    target_compile_definitions(${TARGET_NAME} PRIVATE LEARNOGL_OPENGL_MAJOR=4 LEARNOGL_OPENGL_MINOR=3)
elseif(CMAKE_HOST_APPLE)
    target_compile_definitions(${TARGET_NAME} PRIVATE LEARNOGL_OPENGL_MAJOR=4 LEARNOGL_OPENGL_MINOR=1)
endif()
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
        glfw
        glad::glad
        glm::glm
        fmt::fmt
        spdlog::spdlog
)