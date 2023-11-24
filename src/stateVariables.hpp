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

#include "glad/glad.h"

#include <string>
#include <vector>
#include <tuple>

class CStateVariables
{
public:
    CStateVariables( )                                        = delete;
    ~CStateVariables( )                                       = delete;

    CStateVariables(CStateVariables const & other)            = delete;
    CStateVariables& operator=(CStateVariables const & other) = delete;

    CStateVariables(CStateVariables&& other)                  = delete;
    CStateVariables& operator=(CStateVariables&& other)       = delete;

public:
    static auto getString(GLenum const name) -> std::string;
    static auto getString(GLenum const name, GLuint const index) -> std::string;

    static auto getInteger(GLenum const name) -> GLint;
    static auto getInteger64(GLenum const name) -> GLint64;

    static auto getExtensions( ) -> std::vector<std::string>;
    static auto getPointSizeRange( ) -> std::tuple<GLint, GLint>;

    static auto printString(GLenum const name) -> void;
    static auto printInteger(GLenum const name) -> void;
    static auto printInteger64(GLenum const name) -> void;

    static auto printExtensions( ) -> void;
    static auto printPointSizeRange( ) -> void;

    static auto parameterToString(GLenum const name) -> std::string;

};
