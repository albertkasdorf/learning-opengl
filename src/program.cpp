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

#include <utility>
#include <stdexcept>
#include <string>

Program::Program( )
{
    m_programId = glCreateProgram( );
}

Program::~Program( )
{
    glDeleteProgram(m_programId);
}

Program::Program(Program&& other)
{
    *this = std::move(other);
}

Program& Program::operator=(Program&& other)
{
    if(this != &other)
    {
        // Cleanup existing resources.
        glDeleteProgram(m_programId);

        // Copy the data from source to destination.
        m_programId       = other.m_programId;

        // Cleanup the data from the source.
        other.m_programId = 0;
    }
    return *this;
}

auto Program::getId( ) const -> GLuint
{
    return m_programId;
}

auto Program::attachShader(Shader const & shader) -> void
{
    glAttachShader(m_programId, shader.getId( ));
}

auto Program::link( ) -> void
{
    glLinkProgram(m_programId);

    GLint programLinked;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &programLinked);
    if(programLinked != GL_TRUE)
    {
        GLint logLength{ };
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);

        std::string message{ };
        message.resize(logLength);
        glGetProgramInfoLog(
            m_programId, logLength, &logLength, message.data( ));

        throw std::runtime_error(message);
    }

    glValidateProgram(m_programId);

    GLint validationStatus;
    glGetProgramiv(m_programId, GL_VALIDATE_STATUS, &validationStatus);
    if(validationStatus != GL_TRUE)
    {
        GLint logLength{ };
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);

        std::string message{ };
        message.resize(logLength);
        glGetProgramInfoLog(
            m_programId, logLength, &logLength, message.data( ));

        throw std::runtime_error(message);
    }
}