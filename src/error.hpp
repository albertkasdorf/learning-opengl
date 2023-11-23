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

#include "glad/glad.h"

#define GLCheck(x)                                                                                                     \
CError::clear( );                                                                                                      \
x;                                                                                                                     \
CError::report(#x, __FILE__, __LINE__);

class CError
{
public:
    CError( ) = delete;

public:
    static auto            clear( ) -> void;

    static auto            report(char const * function, char const * file, int const line) -> void;

    static auto            enableDebugOutput(void const * userParam = nullptr) -> void;

    static auto GLAPIENTRY debugMessageCallback(
        GLenum         source,
        GLenum         type,
        GLuint         id,
        GLenum         severity,
        GLsizei        length,
        GLchar const * message,
        void const *   userParam) -> void;
};
