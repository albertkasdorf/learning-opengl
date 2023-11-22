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

#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <array>
#include <array>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <sstream>

// Window dimensions

/// @brief Width of the window
unsigned int const k_screenWidth{800};

/// @brief Height of the window
unsigned int const k_screenHeight{600};

/// @brief Function called when the window is resized
/// @param window Window handle
/// @param width Window width
/// @param height Window height
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
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

/// @brief OpenGL debug callback function
/// @param source
/// @param type
/// @param id
/// @param severity
/// @param length
/// @param message
/// @param userParam
/// @return
void GLAPIENTRY debugCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    GLchar const * message, void const * userParam)
{
    // Output the debug message to the console
    // std::cout << "OpenGL Debug Message: " << message << '\n';
    throw std::runtime_error(message);
}

/// @brief
/// @param vertexShader
/// @param fragmentShader
/// @return
Program createShader(
    std::string const & vertexShaderSource,
    std::string const & fragmentShaderSource)
{
    Shader vertexShader{EShaderType::Vertex};
    vertexShader.compile(vertexShaderSource);

    Shader fragmentShader{EShaderType::Fragment};
    fragmentShader.compile(fragmentShaderSource);

    Program program{ };
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link( );

    return program;
}

/// @brief
/// @param vertexShaderPath
/// @param fragmentShaderPath
/// @return
Program createShader(
    std::filesystem::path const & vertexShaderPath,
    std::filesystem::path const & fragmentShaderPath)
{
    std::ifstream     vertexShaderFile(vertexShaderPath);
    std::ifstream     fragmentShaderFile(fragmentShaderPath);

    std::string const vertexShader{
        std::istreambuf_iterator<std::string::value_type>{vertexShaderFile},
        {}};
    std::string const fragmentShader{
        std::istreambuf_iterator<std::string::value_type>(fragmentShaderFile),
        {}};

    return createShader(vertexShader, fragmentShader);
}

/// @brief
/// @param shaderPath
/// @return
Program createShader(std::filesystem::path const & shaderPath)
{
    enum class EShaderType : std::uint8_t
    {
        Vertex   = 0,
        Fragment = 1,
    };

    std::ifstream                    shaderFile(shaderPath);
    std::string                      line{ };
    EShaderType                      shaderType{ };
    std::array<std::stringstream, 2> shaderTexts{ };

    while(std::getline(shaderFile, line))
    {
        if(std::string::npos != line.find("// shader vertex"))
        {
            shaderType = EShaderType::Vertex;
            continue;
        }
        if(std::string::npos != line.find("// shader fragment"))
        {
            shaderType = EShaderType::Fragment;
            continue;
        }

        std::stringstream& shaderText =
            shaderTexts.at(static_cast<size_t>(shaderType));
        shaderText << line << '\n';
    }

    return createShader(
        shaderTexts.at(static_cast<size_t>(EShaderType::Vertex)).str( ),
        shaderTexts.at(static_cast<size_t>(EShaderType::Fragment)).str( ));
}

/// @brief
/// @param argc
/// @param argv
/// @return
auto main(int argc, char** argv) -> int
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
#ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a window object
        GLFWwindow* window{glfwCreateWindow(
            k_screenWidth, k_screenHeight, "GLFW Example", nullptr, nullptr)};
        if(nullptr == window)
        {
            throw std::runtime_error("Failed to create GLFW window.");
        }
        glfwMakeContextCurrent(window);

        // Initialize GLAD: Load OpenGL function pointers
        if(!gladLoadGLLoader(
               reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Failed to initialize GLAD.");
        }

        // Enable OpenGL debug output
#ifndef __APPLE__
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(&debugCallback, 0);
#endif

        // Set viewport size and register resize callback
        glViewport(0, 0, k_screenWidth, k_screenHeight);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        //----
        std::array<GLfloat, 6> positions{-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
        GLuint                 vbo{ };
        GLuint                 vao{ };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), positions.data( ),
            GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

        // GLuint programId{createShader(
        //     std::filesystem::path{"assets/shader/simple.vs"},
        //     std::filesystem::path{"assets/shader/simple.fs"})};
        Program const program{
            createShader(std::filesystem::path{"assets/shader/simple.shader"})};
        glUseProgram(program.getId( ));

        // Main rendering loop
        while(!glfwWindowShouldClose(window))
        {
            // Input handling
            processInput(window);

            // Rendering commands
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // glDrawArrays(GL_LINE_LOOP, 0, 3);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Swap the buffers and poll IO events
            glfwSwapBuffers(window);
            glfwPollEvents( );
        }
    }
    catch(std::exception const & e)
    {
        std::cerr << e.what( ) << '\n';
        returnCode = -1;
    }

    if(GLFW_TRUE == glfwIsInitialized)
    {
        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate( );
    }
    return returnCode;
}