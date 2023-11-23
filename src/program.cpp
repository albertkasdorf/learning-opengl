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
#include "error.hpp"
#include "shaderParser.hpp"
#include "shader.hpp"

#include "fmt/core.h"

#include <utility>
#include <stdexcept>
#include <string>

CProgram::CProgram( )
{
}

CProgram::~CProgram( )
{
    destroy( );
}

CProgram::CProgram(CProgram&& other)
{
    *this = std::move(other);
}

CProgram& CProgram::operator=(CProgram&& other)
{
    if(this != &other)
    {
        destroy( );
        m_programId            = std::exchange(other.m_programId, { });
        m_uniformLocationCache = std::exchange(other.m_uniformLocationCache, { });
    }
    return *this;
}

auto CProgram::getId( ) const -> GLuint
{
    return m_programId;
}

auto CProgram::use( ) const -> void
{
    GLCheck(glUseProgram(m_programId));
}

auto CProgram::setUniform(std::string const & name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) -> void
{
    GLint const location{getUniformLocation(name)};
    GLCheck(glUniform4f(location, v0, v1, v2, v3));
}

auto CProgram::getUniformLocation(std::string const & name) -> GLint
{
    auto const iter{m_uniformLocationCache.find(name)};
    if(iter != m_uniformLocationCache.end( ))
    {
        return std::get<1>(*iter);
    }

    GLCheck(GLint const location = glGetUniformLocation(m_programId, name.c_str( )));
    if(-1 == location)
    {
        throw std::runtime_error(fmt::format(R"(Location of the uniform variable "{}" can not be found.)", name));
    }

    m_uniformLocationCache.insert_or_assign(name, location);
    return location;
}

auto CProgram::create(std::filesystem::path const & shaderFilePath) -> void
{
    destroy( );

    CShaderParser parser{ };
    parser.parse(shaderFilePath);

    CShader vertexShader{ };
    vertexShader.create(EShaderType::Vertex, parser.getVertexShaderSource( ));

    CShader fragmentShader{ };
    fragmentShader.create(EShaderType::Fragment, parser.getFragmentShaderSource( ));

    GLCheck(m_programId = glCreateProgram( ));
    if(0 == m_programId)
    {
        throw std::runtime_error("glCreateProgram returned zero.");
    }

    GLCheck(glAttachShader(m_programId, vertexShader.getId( )));
    GLCheck(glAttachShader(m_programId, fragmentShader.getId( )));

    GLint programLinked{ };
    GLCheck(glLinkProgram(m_programId));
    GLCheck(glGetProgramiv(m_programId, GL_LINK_STATUS, &programLinked));
    if(programLinked != GL_TRUE)
    {
        GLint logLength{ };
        GLCheck(glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength));

        std::string message{ };
        message.resize(logLength);
        GLCheck(glGetProgramInfoLog(m_programId, logLength, &logLength, message.data( )));

        throw std::runtime_error(message);
    }

    GLint validationStatus{ };
    GLCheck(glValidateProgram(m_programId));
    GLCheck(glGetProgramiv(m_programId, GL_VALIDATE_STATUS, &validationStatus));
    if(validationStatus != GL_TRUE)
    {
        GLint logLength{ };
        GLCheck(glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength));

        std::string message{ };
        message.resize(logLength);
        GLCheck(glGetProgramInfoLog(m_programId, logLength, &logLength, message.data( )));

        throw std::runtime_error(message);
    }
}

auto CProgram::destroy( ) -> void
{
    if(0 != m_programId)
    {
        GLCheck(glDeleteProgram(m_programId));
        m_programId = { };
    }
    m_uniformLocationCache.clear( );
}
