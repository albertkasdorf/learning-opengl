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

#pragma once

#include "shaderType.hpp"

#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"

#include <string>

class Shader
{
public:
    explicit Shader(EShaderType const shaderType);
    ~Shader( );

    Shader(Shader const & other)            = delete;
    Shader& operator=(Shader const & other) = delete;

    Shader(Shader&& other);
    Shader& operator=(Shader&& other);

public:
    auto getId( ) const -> GLuint;

    auto compile(std::string const & source) -> void;

private:
    GLuint m_shaderId{ };
};