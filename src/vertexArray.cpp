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

#include "vertexArray.hpp"
#include "error.hpp"

#include <utility>
#include <algorithm>

CVertexArray::~CVertexArray( )
{
    destroy( );
}

CVertexArray::CVertexArray(CVertexArray&& other)
{
    *this = std::move(other);
}

CVertexArray& CVertexArray::operator=(CVertexArray&& other)
{
    if(this != &other)
    {
        destroy( );
        m_vertexArrayId = std::exchange(other.m_vertexArrayId, { });
    }
    return *this;
}

auto CVertexArray::create( ) -> void
{
    destroy( );

    GLCheck(glGenVertexArrays(1, &m_vertexArrayId));
}

auto CVertexArray::destroy( ) -> void
{
    if(0 == m_vertexArrayId)
    {
        return;
    }
    GLCheck(glDeleteVertexArrays(1, &m_vertexArrayId));
    m_vertexArrayId = { };
}

auto CVertexArray::bind( ) const -> void
{
    GLCheck(glBindVertexArray(m_vertexArrayId));
}

auto CVertexArray::unbind( ) const -> void
{
    GLCheck(glBindVertexArray(0));
}

auto CVertexArray::addVertexBuffer(
    CVertexBuffer const & vertexBuffer, CVertexBufferLayout const & vertexBufferLayout) const -> void
{
    bind( );
    vertexBuffer.bind( );

    std::vector<CVertexBufferElement> const & elements{vertexBufferLayout.getElements( )};
    GLsizei const                             stride{vertexBufferLayout.getStride( )};
    GLsizeiptr                                offset{ };

    std::for_each(elements.begin( ), elements.end( ), [stride, &offset](CVertexBufferElement const & element) {
        GLCheck(glEnableVertexAttribArray(static_cast<GLuint>(element.m_vertexAttributeIndex)));
        GLCheck(glVertexAttribPointer(
            static_cast<GLuint>(element.m_vertexAttributeIndex), static_cast<GLint>(element.m_numComponents),
            element.m_componentType, element.m_normalized, stride, reinterpret_cast<void*>(offset)));

        offset += (element.m_componentSize * static_cast<GLint>(element.m_numComponents));
    });

    unbind();
    vertexBuffer.unbind();
}

auto CVertexArray::addIndexBuffer(CIndexBuffer const & indexBuffer) const -> void
{
    bind();
    indexBuffer.bind();
    unbind();
    indexBuffer.unbind();
}
