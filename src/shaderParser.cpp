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

#include "shaderParser.hpp"

#include <cstdint>
#include <array>
#include <fstream>
#include <sstream>

auto CShaderParser::parse(std::filesystem::path const & shaderFilePath) -> void
{
    enum class EShaderType : std::uint8_t
    {
        Vertex   = 0,
        Fragment = 1,
    };

    std::ifstream                    shaderFile(shaderFilePath);
    std::string                      line{ };
    EShaderType                      shaderType{ };
    std::array<std::stringstream, 2> shaderTexts{ };

    while(std::getline(shaderFile, line))
    {
        if(std::string::npos != line.find("// shader vertex"))
        {
            shaderType = EShaderType::Vertex;
            continue;
        }
        if(std::string::npos != line.find("// shader fragment"))
        {
            shaderType = EShaderType::Fragment;
            continue;
        }

        std::stringstream& shaderText = shaderTexts.at(static_cast<size_t>(shaderType));
        shaderText << line << '\n';
    }

    m_shaderFilePath       = shaderFilePath;
    m_vertexShaderSource   = shaderTexts.at(static_cast<size_t>(EShaderType::Vertex)).str( );
    m_fragmentShaderSource = shaderTexts.at(static_cast<size_t>(EShaderType::Fragment)).str( );
}

auto CShaderParser::getShaderFilePath( ) const -> std::filesystem::path
{
    return m_shaderFilePath;
}

auto CShaderParser::getVertexShaderSource( ) const -> std::string
{
    return m_vertexShaderSource;
}

auto CShaderParser::getFragmentShaderSource( ) const -> std::string
{
    return m_fragmentShaderSource;
}
