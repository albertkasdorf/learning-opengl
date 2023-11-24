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
#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "vertexBufferLayout.hpp"
#include "stateVariables.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <array>
#include <filesystem>

// Window dimensions
unsigned int const k_screenWidth{800};
unsigned int const k_screenHeight{600};

void               framebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height)
{
    GLCheck(glViewport(0, 0, width, height));
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

auto printStateVariables( ) -> void
{
    CStateVariables::printInteger(GL_MAJOR_VERSION);
    CStateVariables::printInteger(GL_MINOR_VERSION);
    CStateVariables::printString(GL_VENDOR);
    CStateVariables::printString(GL_RENDERER);
    CStateVariables::printString(GL_VERSION);
    CStateVariables::printString(GL_SHADING_LANGUAGE_VERSION);

    CStateVariables::printInteger(GL_MAX_VERTEX_ATTRIBS);
    CStateVariables::printInteger64(GL_MAX_ELEMENTS_VERTICES);
    CStateVariables::printInteger64(GL_MAX_ELEMENTS_INDICES);
    CStateVariables::printInteger(GL_MAX_DRAW_BUFFERS);
    CStateVariables::printInteger64(GL_MAX_TEXTURE_BUFFER_SIZE);
    CStateVariables::printInteger(GL_MAX_TEXTURE_IMAGE_UNITS);
    CStateVariables::printInteger(GL_MAX_TEXTURE_SIZE);
#ifdef __APPLE__
#else
    CStateVariables::printInteger(GL_MAX_UNIFORM_LOCATIONS);
    CStateVariables::printInteger64(GL_MAX_ELEMENT_INDEX);
#endif

    CStateVariables::printPointSizeRange( );

    CStateVariables::printInteger(GL_NUM_EXTENSIONS);
    // CStateVariables::printExtensions( );
}

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
        // Specifies which OpenGL profile to create the context for.
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality
        // deprecated in the requested version of OpenGL is removed.
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        // Specifies whether the context should be created in debug mode, which may provide additional error and
        // diagnostic reporting functionality.
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

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

        // Enable OpenGL debug output
        CError::enableDebugOutput( );

        printStateVariables( );

        // Set viewport size and register resize callback
        GLCheck(glViewport(0, 0, k_screenWidth, k_screenHeight));
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        // ???
        // glfwSwapInterval

        //----
        std::array<GLfloat, 9> positions{
            // clang-format off
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f,
            // clang-format on
        };
        std::array<GLfloat, 3> pointSizes{
            // clang-format off
            10.0F, 5.0F, 25.0F
            // clang-format on
        };
        std::array<GLuint, 3> indicies{
            // clang-format off
            0, 1, 2
            // clang-format on
        };

        struct CVertex
        {
            GLfloat m_x{ };
            GLfloat m_y{ };
            GLuint  m_ptSize{ };
        };

        std::array<CVertex, 3> vertices{
            {{-0.6f, -0.6f, 10}, {0.0f, 0.6f, 5}, {0.6f, -0.6f, 25}}
        };

        CVertexBuffer vbo{ };
        vbo.create(positions.data( ), sizeof(GLfloat), positions.size( ));

        CVertexBufferLayout vboLayout{ };
        vboLayout.addFloat(EVertexAttributeIndex::Zero, ENumberOfComponents::Two);

        CVertexBuffer vbPointSizes{ };
        vbPointSizes.create(pointSizes.data( ), sizeof(GLfloat), pointSizes.size( ));

        CVertexBufferLayout vbPointSizesLayout{ };
        vbPointSizesLayout.addFloat(EVertexAttributeIndex::One, ENumberOfComponents::One);

        CVertexBuffer vbVertices{ };
        vbVertices.create(vertices.data( ), sizeof(CVertex), vertices.size( ));

        CVertexBufferLayout vbVerticesLayout{ };
        vbVerticesLayout.addFloat(EVertexAttributeIndex::Zero, ENumberOfComponents::Two);
        vbVerticesLayout.addUInt(EVertexAttributeIndex::One, ENumberOfComponents::One);

        CIndexBuffer ibo{ };
        ibo.create(indicies.data( ), indicies.size( ));

        CVertexArray vao{ };
        vao.create( );
        vao.addVertexBuffer(vbo, vboLayout);
        vao.addVertexBuffer(vbPointSizes, vbPointSizesLayout);
        // vao.addVertexBuffer(vbVertices, vbVerticesLayout);
        vao.addIndexBuffer(ibo);

        CProgram program{ };
        vao.bind();
        program.create(std::filesystem::path{"assets/shader/simple.shader"});
        vao.unbind();

        GLCheck(glEnable(GL_PROGRAM_POINT_SIZE));

        // Main rendering loop
        while(!glfwWindowShouldClose(window))
        {
            // Input handling
            processInput(window);

            // Rendering commands
            GLCheck(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            vao.bind( );
            program.bind( );

            program.setUniform("u_color", 1.0F, 0.0F, 0.0F, 1.0F);
            GLCheck(glDrawArrays(GL_TRIANGLES, 0, 3));

            program.setUniform("u_color", 0.0F, 1.0F, 0.0F, 1.0F);
            GLCheck(glDrawArrays(GL_LINE_LOOP, 0, 3));

            program.setUniform("u_color", 1.0F, 1.0F, 1.0F, 1.0F);
            GLCheck(glDrawArrays(GL_POINTS, 0, 3));

            // program.setUniform("u_color", 0.2F, 0.3F, 0.8F, 1.0F);
            // GLCheck(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indicies.size( )), GL_UNSIGNED_INT, nullptr));

            // program.setUniform("u_color", 0.8F, 0.3F, 0.8F, 1.0F);
            // GLCheck(glDrawElements(GL_POINTS, static_cast<GLsizei>(indicies.size( )), GL_UNSIGNED_INT, nullptr));

            program.unbind( );
            vao.unbind( );

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