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

#include "error.hpp"

#include "fmt/core.h"

#include <string>
#include <iostream>
#include <cassert>

auto CError::clear( ) -> void
{
    while(GL_NO_ERROR != glGetError( ))
    {
    }
}

auto CError::report(char const * function, char const * file, int const line) -> void
{
    GLenum const error{glGetError( )};
    if(GL_NO_ERROR == error)
    {
        return;
    }

    std::string       strError{ };

    // clang-format off
    switch(error)
    {
    case GL_NO_ERROR:                       strError = "GL_NO_ERROR"; break;
    case GL_INVALID_ENUM:                   strError = "GL_INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                  strError = "GL_INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:              strError = "GL_INVALID_OPERATION"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:  strError = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
    case GL_OUT_OF_MEMORY:                  strError = "GL_OUT_OF_MEMORY"; break;
    case GL_STACK_UNDERFLOW:                strError = "GL_STACK_UNDERFLOW"; break;
    case GL_STACK_OVERFLOW:                 strError = "GL_STACK_OVERFLOW"; break;
    default:                                strError = fmt::format("{}", error); break;
    }
    // clang-format on

    std::string const errorMessage{fmt::format(
        R"(OpenGL error "{}" reported during the call of "{}" in "{}:{}".\n)", strError, function, file, line)};
    throw std::runtime_error(errorMessage);
}

auto CError::enableDebugOutput(void const * userParam) -> void
{
#ifndef __APPLE__
    GLCheck(glEnable(GL_DEBUG_OUTPUT));
    GLCheck(glDebugMessageCallback(&CError::debugMessageCallback, userParam));
#endif
}

auto CError::debugMessageCallback(
    GLenum                        source,
    GLenum                        type,
    GLuint                        id,
    GLenum                        severity,
    [[maybe_unused]] GLsizei      length,
    GLchar const *                message,
    [[maybe_unused]] void const * userParam) -> void
{
    std::string       strSource{ };
    std::string       strType{ };
    std::string       strSeverity{ };

    // clang-format off
    switch(source)
    {
    case GL_DEBUG_SOURCE_API:               strSource = "GL_DEBUG_SOURCE_API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     strSource = "GL_DEBUG_SOURCE_WINDOW_SYSTEM"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:   strSource = "GL_DEBUG_SOURCE_SHADER_COMPILER"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:       strSource = "GL_DEBUG_SOURCE_THIRD_PARTY"; break;
    case GL_DEBUG_SOURCE_APPLICATION:       strSource = "GL_DEBUG_SOURCE_APPLICATION"; break;
    case GL_DEBUG_SOURCE_OTHER:             strSource = "GL_DEBUG_SOURCE_OTHER"; break;
    }

    switch(type)
    {
    case GL_DEBUG_TYPE_ERROR:               strType = "GL_DEBUG_TYPE_ERROR"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: strType = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  strType = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         strType = "GL_DEBUG_TYPE_PORTABILITY"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         strType = "GL_DEBUG_TYPE_PERFORMANCE"; break;
    case GL_DEBUG_TYPE_OTHER:               strType = "GL_DEBUG_TYPE_OTHER"; break;
    case GL_DEBUG_TYPE_MARKER:              strType = "GL_DEBUG_TYPE_MARKER"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          strType = "GL_DEBUG_TYPE_PUSH_GROUP"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           strType = "GL_DEBUG_TYPE_POP_GROUP"; break;
    }

    switch(severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:            strSeverity = "GL_DEBUG_SEVERITY_HIGH"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:          strSeverity = "GL_DEBUG_SEVERITY_MEDIUM"; break;
    case GL_DEBUG_SEVERITY_LOW:             strSeverity = "GL_DEBUG_SEVERITY_LOW"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:    strSeverity = "GL_DEBUG_SEVERITY_NOTIFICATION"; break;
    }
    // clang-format on

    std::string const errorMessage{fmt::format(
        R"(Source: {}, Type: {}, Id: {}, Severity: {}, Message: "{}".)", strSource, strType, id, strSeverity, message)};

#ifdef _WIN64
    __debugbreak( );
#endif

    throw std::runtime_error(errorMessage);
}