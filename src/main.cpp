#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <iostream>

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
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

auto main(int argc, char** argv) -> int
{
    // Initialize GLFW
    if(!glfwInit( ))
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow* window{glfwCreateWindow(
        k_screenWidth, k_screenHeight, "GLFW Example", nullptr, nullptr)};
    if(!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate( );
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD: Load OpenGL function pointers
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Enable OpenGL debug output
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(debugCallback, 0);

    // Set viewport size and register resize callback
    glViewport(0, 0, k_screenWidth, k_screenHeight);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Main rendering loop
    while(!glfwWindowShouldClose(window))
    {
        // Input handling
        processInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents( );
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    return 0;
}