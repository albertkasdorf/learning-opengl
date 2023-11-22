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

#include "shader.hpp"

#include <utility>
#include <stdexcept>
#include <string>

Shader::Shader(EShaderType const shaderType)
{
    m_shaderId = glCreateShader(static_cast<GLenum>(shaderType));
}

Shader::~Shader( )
{
    glDeleteShader(m_shaderId);
}

Shader::Shader(Shader&& other)
{
    *this = std::move(other);
}

Shader& Shader::operator=(Shader&& other)
{
    if(this != &other)
    {
        // Cleanup existing resources.
        glDeleteShader(m_shaderId);

        // Copy the data from source to destination.
        m_shaderId       = other.m_shaderId;

        // Cleanup the data from the source.
        other.m_shaderId = 0;
    }
    return *this;
}

auto Shader::getId( ) const -> GLuint
{
    return m_shaderId;
}

auto Shader::compile(std::string const & source) -> void
{
    GLchar const * c_str = source.c_str( );
    glShaderSource(m_shaderId, 1, &c_str, nullptr);
    glCompileShader(m_shaderId);

    GLint result{ };
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &result);
    if(GL_FALSE == result)
    {
        GLint logLength{ };
        glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &logLength);

        std::string message{ };
        message.resize(logLength);
        glGetShaderInfoLog(m_shaderId, logLength, &logLength, message.data( ));
        
        throw std::runtime_error(message);
    }
}