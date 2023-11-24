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

#include "vertexBufferLayout.hpp"

auto CVertexBufferLayout::addFloat(EVertexAttributeIndex vertexAttributeIndex, ENumberOfComponents numComponents)
    -> void
{
    m_elements.push_back({vertexAttributeIndex, numComponents, GL_FLOAT, sizeof(GLfloat), GL_FALSE});
    m_stride += static_cast<GLint>(numComponents) * sizeof(GLfloat);
}

auto CVertexBufferLayout::addInt(
    EVertexAttributeIndex vertexAttributeIndex, ENumberOfComponents numComponents, GLboolean normalized) -> void
{
    m_elements.push_back({vertexAttributeIndex, numComponents, GL_INT, sizeof(GLint), normalized});
    m_stride += static_cast<GLint>(numComponents) * sizeof(GLint);
}

auto CVertexBufferLayout::addUInt(
    EVertexAttributeIndex vertexAttributeIndex, ENumberOfComponents numComponents, GLboolean normalized) -> void
{
    m_elements.push_back({vertexAttributeIndex, numComponents, GL_UNSIGNED_INT, sizeof(GLuint), normalized});
    m_stride += static_cast<GLint>(numComponents) * sizeof(GLuint);
}

auto CVertexBufferLayout::getStride( ) const -> GLsizei
{
    return m_stride;
}

auto CVertexBufferLayout::getElements( ) const -> std::vector<CVertexBufferElement> const &
{
    return m_elements;
}
