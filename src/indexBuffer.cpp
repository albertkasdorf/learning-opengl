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

#include "indexBuffer.hpp"
#include "error.hpp"

#include <utility>

CIndexBuffer::~CIndexBuffer( )
{
    destroy( );
}

CIndexBuffer::CIndexBuffer(CIndexBuffer&& other)
{
    *this = std::move(other);
}

CIndexBuffer& CIndexBuffer::operator=(CIndexBuffer&& other)
{
    if(this != &other)
    {
        destroy( );
        m_indexBufferId = std::exchange(other.m_indexBufferId, { });
    }
    return *this;
}

auto CIndexBuffer::create(GLuint const * const data, GLsizeiptr const count, EBufferUsagePattern const usage) -> void
{
    destroy( );

    GLCheck(glGenBuffers(1, &m_indexBufferId));
    bind();
    GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, static_cast<GLenum>(usage)));
    unbind();
}

auto CIndexBuffer::destroy( ) -> void
{
    if(0 == m_indexBufferId)
    {
        return;
    }
    GLCheck(glDeleteBuffers(1, &m_indexBufferId));
    m_indexBufferId = { };
}

auto CIndexBuffer::getId( ) const -> GLuint
{
    return m_indexBufferId;
}

auto CIndexBuffer::bind( ) const -> void
{
    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));
}

auto CIndexBuffer::unbind( ) const -> void
{
    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
