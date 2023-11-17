#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "fmt/core.h"

#include <iostream>
#include <array>
#include <array>
#include <fstream>
#include <filesystem>
#include <iterator>

// Window dimensions
unsigned int const k_screenWidth{800};
unsigned int const k_screenHeight{600};

// Function called when the window is resized
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Function to process input (e.g., escape key to close the window)
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// OpenGL debug callback function
void GLAPIENTRY debugCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    GLchar const * message, void const * userParam)
{
    // Output the debug message to the console
    // std::cout << "OpenGL Debug Message: " << message << '\n';
    throw std::runtime_error(message);
}

GLuint compileShader(GLenum type, std::string const & source)
{
    GLuint const   shaderId{glCreateShader(type)};
    GLchar const * c_str = source.c_str( );
    glShaderSource(shaderId, 1, &c_str, nullptr);
    glCompileShader(shaderId);

    GLint result{ };
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if(GL_FALSE == result)
    {
        GLint logLength{ };
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        std::string message{ };
        message.resize(logLength);
        glGetShaderInfoLog(shaderId, logLength, &logLength, message.data( ));
        std::cerr << message;
    }

    return shaderId;
}

GLuint createShader(
    std::string const & vertexShader, std::string const & fragmentShader)
{
    GLuint const programId{glCreateProgram( )};
    GLuint const vertexShaderId{compileShader(GL_VERTEX_SHADER, vertexShader)};
    GLuint const fragmentShaderId{
        compileShader(GL_FRAGMENT_SHADER, fragmentShader)};

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    glValidateProgram(programId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

GLuint createShader(
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(&debugCallback, 0);

        // Set viewport size and register resize callback
        // glViewport(0, 0, k_screenWidth, k_screenHeight);
        // glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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

        GLuint programId{createShader(
            std::filesystem::path{"assets/shader/simple.vs"},
            std::filesystem::path{"assets/shader/simple.fs"})};
        glUseProgram(programId);

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