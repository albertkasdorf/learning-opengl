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

#include "vertexBuffer.hpp"
#include "error.hpp"

#include <utility>

CVertexBuffer::~CVertexBuffer( )
{
    destroy( );
}

CVertexBuffer::CVertexBuffer(CVertexBuffer&& other)
{
    *this = std::move(other);
}

CVertexBuffer& CVertexBuffer::operator=(CVertexBuffer&& other)
{
    if(this != &other)
    {
        destroy( );
        m_vertexBufferId = std::exchange(other.m_vertexBufferId, { });
    }
    return *this;
}

auto CVertexBuffer::create(
    GLvoid const * const data, GLsizeiptr const size, GLsizeiptr const count, EBufferUsagePattern const usage) -> void
{
    destroy( );

    GLCheck(glGenBuffers(1, &m_vertexBufferId));
    bind( );
    GLCheck(glBufferData(GL_ARRAY_BUFFER, size * count, data, static_cast<GLenum>(usage)));
    unbind( );
}

auto CVertexBuffer::destroy( ) -> void
{
    if(0 == m_vertexBufferId)
    {
        return;
    }
    GLCheck(glDeleteBuffers(1, &m_vertexBufferId));
    m_vertexBufferId = { };
}

auto CVertexBuffer::getId( ) const -> GLuint
{
    return m_vertexBufferId;
}

auto CVertexBuffer::bind( ) const -> void
{
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));
}

auto CVertexBuffer::unbind( ) const -> void
{
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
