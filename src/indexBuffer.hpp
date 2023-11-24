/// ----------------------------------------------------------------------------
/// MIT License
///
/// @copyright Copyright (c) 2023 Albert Kasdorf
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
/// ----------------------------------------------------------------------------
/// @file
/// @author albert.kasdorf@live.de
/// ----------------------------------------------------------------------------

#pragma once

#include "bufferUsagePattern.hpp"

#include "glad/glad.h"

class CIndexBuffer
{
public:
    CIndexBuffer( ) = default;
    ~CIndexBuffer( );

    CIndexBuffer(CIndexBuffer const & other)            = delete;
    CIndexBuffer& operator=(CIndexBuffer const & other) = delete;

    CIndexBuffer(CIndexBuffer&& other);
    CIndexBuffer& operator=(CIndexBuffer&& other);

public:
    auto create(
        GLuint const * const      data,
        GLsizeiptr const          count,
        EBufferUsagePattern const usage = EBufferUsagePattern::StaticDraw) -> void;
    auto destroy( ) -> void;

    auto getId( ) const -> GLuint;

    auto bind( ) const -> void;
    auto unbind( ) const -> void;

private:
    GLuint m_indexBufferId{ };
};