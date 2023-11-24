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
#include "error.hpp"

#include <utility>
#include <stdexcept>
#include <string>

CShader::~CShader( )
{
    destroy( );
}

CShader::CShader(CShader&& other)
{
    *this = std::move(other);
}

CShader& CShader::operator=(CShader&& other)
{
    if(this != &other)
    {
        destroy( );
        m_shaderId = std::exchange(other.m_shaderId, { });
    }
    return *this;
}

auto CShader::getId( ) const -> GLuint
{
    return m_shaderId;
}

auto CShader::create(EShaderType const shaderType, std::string const & source) -> void
{
    destroy( );

    GLCheck(m_shaderId = glCreateShader(static_cast<GLenum>(shaderType)));
    if(0 == m_shaderId)
    {
        throw std::runtime_error("glCreateShader returned zero.");
    }

    GLchar const * c_str = source.c_str( );
    GLCheck(glShaderSource(m_shaderId, 1, &c_str, nullptr));
    GLCheck(glCompileShader(m_shaderId));

    GLint result{ };
    GLCheck(glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &result));
    if(GL_FALSE == result)
    {
        GLint logLength{ };
        GLCheck(glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &logLength));

        std::string message{ };
        message.resize(logLength);
        GLCheck(glGetShaderInfoLog(m_shaderId, logLength, &logLength, message.data( )));

        throw std::runtime_error(message);
    }
}

auto CShader::destroy( ) -> void
{
    if(0 == m_shaderId)
    {
        return;
    }

    GLCheck(glDeleteShader(m_shaderId));
    m_shaderId = { };
}
