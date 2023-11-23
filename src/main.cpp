/// ----------------------------------------------------------------------------
/// MIT License
///
/// @copyright Copyright (c) 2023 Albert Kasdorf
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to
/// deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
/// ----------------------------------------------------------------------------
/// @file
/// @author albert.kasdorf@live.de
/// ----------------------------------------------------------------------------

#include "program.hpp"
#include "shader.hpp"
#include "error.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <array>
#include <filesystem>

// Window dimensions

/// @brief Width of the window
unsigned int const k_screenWidth{800};

/// @brief Height of the window
unsigned int const k_screenHeight{600};

/// @brief Function called when the window is resized
/// @param window Window handle
/// @param width Window width
/// @param height Window height
void               framebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/// @brief Function to process input (e.g., escape key to close the window)
/// @param window
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

/// @brief
/// @param argc
/// @param argv
/// @return
auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int
{
    int glfwIsInitialized{GLFW_FALSE};
    int returnCode{ };

    try
    {
        // Initialize GLFW
        glfwIsInitialized = glfwInit( );
        if(GLFW_FALSE == glfwIsInitialized)
        {
            throw std::runtime_error("Failed to initialize GLFW.");
        }

        // Configure GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LEARNOGL_OPENGL_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LEARNOGL_OPENGL_MINOR);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a window object
        GLFWwindow* window{glfwCreateWindow(k_screenWidth, k_screenHeight, "GLFW Example", nullptr, nullptr)};
        if(nullptr == window)
        {
            throw std::runtime_error("Failed to create GLFW window.");
        }
        glfwMakeContextCurrent(window);

        // Initialize GLAD: Load OpenGL function pointers
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Failed to initialize GLAD.");
        }
        std::cout << GLVersion.major << " " << GLVersion.minor << "\n";

        // Enable OpenGL debug output
        CError::enableDebugOutput( );

        GLint maxVertexAttribs{ };
        GLCheck(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs));
        std::cout << fmt::format("GL_MAX_VERTEX_ATTRIBS: {}\n", maxVertexAttribs);

        GLint majorVersion{ };
        GLint minorVersion{ };
        GLCheck(glGetIntegerv(GL_MAJOR_VERSION, &majorVersion));
        GLCheck(glGetIntegerv(GL_MINOR_VERSION, &minorVersion));
        std::cout << fmt::format("GL_MAJOR_VERSION, GL_MINOR_VERSION: {}.{}\n", majorVersion, minorVersion);

        // Set viewport size and register resize callback
        glViewport(0, 0, k_screenWidth, k_screenHeight);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        // ???
        // glfwSwapInterval

        //----
        std::array<GLfloat, 6> positions{
            // clang-format off
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
            // clang-format om
        };
        std::array<GLuint, 3>  indicies{
            // clang-format off
            0, 1, 2
            // clang-format on
        };
        GLuint vbo{ };
        GLuint vao{ };
        GLuint ibo{ };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, positions.size( ) * sizeof(GLfloat), positions.data( ), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size( ) * sizeof(GLuint), indicies.data( ), GL_STATIC_DRAW);

        CProgram program{ };
        program.create(std::filesystem::path{"assets/shader/simple.shader"});

        GLCheck(glEnable(GL_PROGRAM_POINT_SIZE));

        // Main rendering loop
        while(!glfwWindowShouldClose(window))
        {
            // Input handling
            processInput(window);

            // Rendering commands
            GLCheck(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            // glDrawArrays(GL_LINE_LOOP, 0, 3);
            // glDrawArrays(GL_TRIANGLES, 0, 3);

            program.use( );

            program.setUniform("u_color", 0.2F, 0.3F, 0.8F, 1.0F);
            GLCheck(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indicies.size( )), GL_UNSIGNED_INT, nullptr));

            program.setUniform("u_color", 0.8F, 0.3F, 0.8F, 1.0F);
            GLCheck(glDrawElements(GL_POINTS, static_cast<GLsizei>(indicies.size( )), GL_UNSIGNED_INT, nullptr));

            // Swap the buffers and poll IO events
            glfwSwapBuffers(window);
            glfwPollEvents( );
        }
    }
    catch(std::exception const & e)
    {
        std::cout << e.what( ) << '\n';
        returnCode = -1;
    }

    if(GLFW_TRUE == glfwIsInitialized)
    {
        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate( );
    }
    return returnCode;
}