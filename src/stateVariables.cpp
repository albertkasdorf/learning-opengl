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

#include "stateVariables.hpp"
#include "error.hpp"

#include "fmt/core.h"

#include <array>

auto CStateVariables::getExtensions( ) -> std::vector<std::string>
{
    GLint const              numExtensions{getInteger(GL_NUM_EXTENSIONS)};
    std::vector<std::string> extensions{ };

    for(GLint i{ }; i < numExtensions; ++i)
    {
        extensions.push_back(getString(GL_EXTENSIONS, i));
    }

    return extensions;
}

auto CStateVariables::getPointSizeRange( ) -> std::tuple<GLint, GLint>
{
    std::array<GLint, 2> range{ };
    GLCheck(glGetIntegerv(GL_POINT_SIZE_RANGE, range.data( )));
    return std::make_tuple(range.at(0), range.at(1));
}

auto CStateVariables::getString(GLenum const name) -> std::string
{
    GLCheck(GLubyte const * value = glGetString(name));
    std::string const strValue{reinterpret_cast<std::string::value_type const *>(value)};
    return strValue;
}

auto CStateVariables::getString(GLenum const name, GLuint const index) -> std::string
{
    GLCheck(GLubyte const * value{glGetStringi(name, index)});
    std::string const strValue{reinterpret_cast<std::string::value_type const *>(value)};
    return strValue;
}

auto CStateVariables::getInteger(GLenum const name) -> GLint
{
    GLint value{ };
    GLCheck(glGetIntegerv(name, &value));
    return value;
}

auto CStateVariables::getInteger64(GLenum const name) -> GLint64
{
    GLint64 value{ };
    GLCheck(glGetInteger64v(name, &value));
    return value;
}

auto CStateVariables::printString(GLenum const name) -> void
{
    fmt::println("{}: {}", parameterToString(name), getString(name));
}

auto CStateVariables::printInteger(GLenum const name) -> void
{
    fmt::println("{}: {}", parameterToString(name), getInteger(name));
}

auto CStateVariables::printInteger64(GLenum const name) -> void
{
    fmt::println("{}: {}", parameterToString(name), getInteger64(name));
}

auto CStateVariables::printExtensions( ) -> void
{
    std::vector<std::string> extensions{CStateVariables::getExtensions( )};
    fmt::println("{}:", parameterToString(GL_EXTENSIONS));
    std::for_each(extensions.begin( ), extensions.end( ), [](std::string const & extension) {
        fmt::println("- {}", extension);
    });
}

auto CStateVariables::printPointSizeRange( ) -> void
{
    std::tuple<GLint, GLint> pointSizeRange{CStateVariables::getPointSizeRange( )};
    fmt::println(
        "{}: [{}, {}]", parameterToString(GL_POINT_SIZE_RANGE), std::get<0>(pointSizeRange),
        std::get<1>(pointSizeRange));
}

auto CStateVariables::parameterToString(GLenum const name) -> std::string
{
    std::string value{ };
    // clang-format off
    switch(name)
    {
    case GL_VENDOR: value = "GL_VENDOR"; break;
    case GL_RENDERER: value = "GL_RENDERER"; break;
    case GL_VERSION: value = "GL_VERSION"; break;
    case GL_SHADING_LANGUAGE_VERSION: value = "GL_SHADING_LANGUAGE_VERSION"; break;
    case GL_EXTENSIONS: value = "GL_EXTENSIONS"; break;
    case GL_ACTIVE_TEXTURE: value = "GL_ACTIVE_TEXTURE"; break;
    case GL_ALIASED_LINE_WIDTH_RANGE: value = "GL_ALIASED_LINE_WIDTH_RANGE"; break;
    case GL_ARRAY_BUFFER_BINDING: value = "GL_ARRAY_BUFFER_BINDING"; break;
    case GL_BLEND: value = "GL_BLEND"; break;
    case GL_BLEND_COLOR: value = "GL_BLEND_COLOR"; break;
    case GL_BLEND_DST_ALPHA: value = "GL_BLEND_DST_ALPHA"; break;
    case GL_BLEND_DST_RGB: value = "GL_BLEND_DST_RGB"; break;
    case GL_BLEND_EQUATION_RGB: value = "GL_BLEND_EQUATION_RGB"; break;
    case GL_BLEND_EQUATION_ALPHA: value = "GL_BLEND_EQUATION_ALPHA"; break;
    case GL_BLEND_SRC_ALPHA: value = "GL_BLEND_SRC_ALPHA"; break;
    case GL_BLEND_SRC_RGB: value = "GL_BLEND_SRC_RGB"; break;
    case GL_COLOR_CLEAR_VALUE: value = "GL_COLOR_CLEAR_VALUE"; break;
    case GL_COLOR_LOGIC_OP: value = "GL_COLOR_LOGIC_OP"; break;
    case GL_COLOR_WRITEMASK: value = "GL_COLOR_WRITEMASK"; break;
    case GL_COMPRESSED_TEXTURE_FORMATS: value = "GL_COMPRESSED_TEXTURE_FORMATS"; break;
    case GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS: value = "GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS: value = "GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_COMPUTE_UNIFORM_BLOCKS: value = "GL_MAX_COMPUTE_UNIFORM_BLOCKS"; break;
    case GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS: value = "GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS"; break;
    case GL_MAX_COMPUTE_UNIFORM_COMPONENTS: value = "GL_MAX_COMPUTE_UNIFORM_COMPONENTS"; break;
    case GL_MAX_COMPUTE_ATOMIC_COUNTERS: value = "GL_MAX_COMPUTE_ATOMIC_COUNTERS"; break;
    case GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS: value = "GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS"; break;
    case GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS: value = "GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS"; break;
    case GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS: value = "GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS"; break;
    case GL_MAX_COMPUTE_WORK_GROUP_COUNT: value = "GL_MAX_COMPUTE_WORK_GROUP_COUNT"; break;
    case GL_MAX_COMPUTE_WORK_GROUP_SIZE: value = "GL_MAX_COMPUTE_WORK_GROUP_SIZE"; break;
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING: value = "GL_DISPATCH_INDIRECT_BUFFER_BINDING"; break;
    case GL_MAX_DEBUG_GROUP_STACK_DEPTH: value = "GL_MAX_DEBUG_GROUP_STACK_DEPTH"; break;
    case GL_DEBUG_GROUP_STACK_DEPTH: value = "GL_DEBUG_GROUP_STACK_DEPTH"; break;
    case GL_CONTEXT_FLAGS: value = "GL_CONTEXT_FLAGS"; break;
    case GL_CULL_FACE: value = "GL_CULL_FACE"; break;
    case GL_CURRENT_PROGRAM: value = "GL_CURRENT_PROGRAM"; break;
    case GL_DEPTH_CLEAR_VALUE: value = "GL_DEPTH_CLEAR_VALUE"; break;
    case GL_DEPTH_FUNC: value = "GL_DEPTH_FUNC"; break;
    case GL_DEPTH_RANGE: value = "GL_DEPTH_RANGE"; break;
    case GL_DEPTH_TEST: value = "GL_DEPTH_TEST"; break;
    case GL_DEPTH_WRITEMASK: value = "GL_DEPTH_WRITEMASK"; break;
    case GL_DITHER: value = "GL_DITHER"; break;
    case GL_DOUBLEBUFFER: value = "GL_DOUBLEBUFFER"; break;
    case GL_DRAW_BUFFER: value = "GL_DRAW_BUFFER"; break;
    case GL_DRAW_FRAMEBUFFER_BINDING: value = "GL_DRAW_FRAMEBUFFER_BINDING"; break;
    case GL_READ_FRAMEBUFFER_BINDING: value = "GL_READ_FRAMEBUFFER_BINDING"; break;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING: value = "GL_ELEMENT_ARRAY_BUFFER_BINDING"; break;
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT: value = "GL_FRAGMENT_SHADER_DERIVATIVE_HINT"; break;
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT: value = "GL_IMPLEMENTATION_COLOR_READ_FORMAT"; break;
    case GL_IMPLEMENTATION_COLOR_READ_TYPE: value = "GL_IMPLEMENTATION_COLOR_READ_TYPE"; break;
    case GL_LINE_SMOOTH: value = "GL_LINE_SMOOTH"; break;
    case GL_LINE_SMOOTH_HINT: value = "GL_LINE_SMOOTH_HINT"; break;
    case GL_LINE_WIDTH: value = "GL_LINE_WIDTH"; break;
    case GL_LAYER_PROVOKING_VERTEX: value = "GL_LAYER_PROVOKING_VERTEX"; break;
    case GL_LOGIC_OP_MODE: value = "GL_LOGIC_OP_MODE"; break;
    case GL_MAJOR_VERSION: value = "GL_MAJOR_VERSION"; break;
    case GL_MAX_3D_TEXTURE_SIZE: value = "GL_MAX_3D_TEXTURE_SIZE"; break;
    case GL_MAX_ARRAY_TEXTURE_LAYERS: value = "GL_MAX_ARRAY_TEXTURE_LAYERS"; break;
    case GL_MAX_CLIP_DISTANCES: value = "GL_MAX_CLIP_DISTANCES"; break;
    case GL_MAX_COLOR_TEXTURE_SAMPLES: value = "GL_MAX_COLOR_TEXTURE_SAMPLES"; break;
    case GL_MAX_COMBINED_ATOMIC_COUNTERS: value = "GL_MAX_COMBINED_ATOMIC_COUNTERS"; break;
    case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS: value = "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS"; break;
    case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS: value = "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS"; break;
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: value = "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS"; break;
    case GL_MAX_COMBINED_UNIFORM_BLOCKS: value = "GL_MAX_COMBINED_UNIFORM_BLOCKS"; break;
    case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS: value = "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS"; break;
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE: value = "GL_MAX_CUBE_MAP_TEXTURE_SIZE"; break;
    case GL_MAX_DEPTH_TEXTURE_SAMPLES: value = "GL_MAX_DEPTH_TEXTURE_SAMPLES"; break;
    case GL_MAX_DRAW_BUFFERS: value = "GL_MAX_DRAW_BUFFERS"; break;
    case GL_MAX_DUAL_SOURCE_DRAW_BUFFERS: value = "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS"; break;
    case GL_MAX_ELEMENTS_INDICES: value = "GL_MAX_ELEMENTS_INDICES"; break;
    case GL_MAX_ELEMENTS_VERTICES: value = "GL_MAX_ELEMENTS_VERTICES"; break;
    case GL_MAX_FRAGMENT_ATOMIC_COUNTERS: value = "GL_MAX_FRAGMENT_ATOMIC_COUNTERS"; break;
    case GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS: value = "GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_FRAGMENT_INPUT_COMPONENTS: value = "GL_MAX_FRAGMENT_INPUT_COMPONENTS"; break;
    case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: value = "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS"; break;
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS: value = "GL_MAX_FRAGMENT_UNIFORM_VECTORS"; break;
    case GL_MAX_FRAGMENT_UNIFORM_BLOCKS: value = "GL_MAX_FRAGMENT_UNIFORM_BLOCKS"; break;
    case GL_MAX_FRAMEBUFFER_WIDTH: value = "GL_MAX_FRAMEBUFFER_WIDTH"; break;
    case GL_MAX_FRAMEBUFFER_HEIGHT: value = "GL_MAX_FRAMEBUFFER_HEIGHT"; break;
    case GL_MAX_FRAMEBUFFER_LAYERS: value = "GL_MAX_FRAMEBUFFER_LAYERS"; break;
    case GL_MAX_FRAMEBUFFER_SAMPLES: value = "GL_MAX_FRAMEBUFFER_SAMPLES"; break;
    case GL_MAX_GEOMETRY_ATOMIC_COUNTERS: value = "GL_MAX_GEOMETRY_ATOMIC_COUNTERS"; break;
    case GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS: value = "GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_GEOMETRY_INPUT_COMPONENTS: value = "GL_MAX_GEOMETRY_INPUT_COMPONENTS"; break;
    case GL_MAX_GEOMETRY_OUTPUT_COMPONENTS: value = "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS"; break;
    case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS: value = "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS"; break;
    case GL_MAX_GEOMETRY_UNIFORM_BLOCKS: value = "GL_MAX_GEOMETRY_UNIFORM_BLOCKS"; break;
    case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS: value = "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS"; break;
    case GL_MAX_INTEGER_SAMPLES: value = "GL_MAX_INTEGER_SAMPLES"; break;
    case GL_MIN_MAP_BUFFER_ALIGNMENT: value = "GL_MIN_MAP_BUFFER_ALIGNMENT"; break;
    case GL_MAX_LABEL_LENGTH: value = "GL_MAX_LABEL_LENGTH"; break;
    case GL_MAX_PROGRAM_TEXEL_OFFSET: value = "GL_MAX_PROGRAM_TEXEL_OFFSET"; break;
    case GL_MIN_PROGRAM_TEXEL_OFFSET: value = "GL_MIN_PROGRAM_TEXEL_OFFSET"; break;
    case GL_MAX_RECTANGLE_TEXTURE_SIZE: value = "GL_MAX_RECTANGLE_TEXTURE_SIZE"; break;
    case GL_MAX_RENDERBUFFER_SIZE: value = "GL_MAX_RENDERBUFFER_SIZE"; break;
    case GL_MAX_SAMPLE_MASK_WORDS: value = "GL_MAX_SAMPLE_MASK_WORDS"; break;
    case GL_MAX_SERVER_WAIT_TIMEOUT: value = "GL_MAX_SERVER_WAIT_TIMEOUT"; break;
    case GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS: value = "GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS"; break;
    case GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS: value = "GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS"; break;
    case GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS: value = "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS"; break;
    case GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS: value = "GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS: value = "GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_TEXTURE_BUFFER_SIZE: value = "GL_MAX_TEXTURE_BUFFER_SIZE"; break;
    case GL_MAX_TEXTURE_IMAGE_UNITS: value = "GL_MAX_TEXTURE_IMAGE_UNITS"; break;
    case GL_MAX_TEXTURE_LOD_BIAS: value = "GL_MAX_TEXTURE_LOD_BIAS"; break;
    case GL_MAX_TEXTURE_SIZE: value = "GL_MAX_TEXTURE_SIZE"; break;
    case GL_MAX_UNIFORM_BUFFER_BINDINGS: value = "GL_MAX_UNIFORM_BUFFER_BINDINGS"; break;
    case GL_MAX_UNIFORM_BLOCK_SIZE: value = "GL_MAX_UNIFORM_BLOCK_SIZE"; break;
    case GL_MAX_UNIFORM_LOCATIONS: value = "GL_MAX_UNIFORM_LOCATIONS"; break;
    // case GL_MAX_VARYING_COMPONENTS: value = "GL_MAX_VARYING_COMPONENTS"; break;
    // case GL_MAX_VARYING_FLOATS: value = "GL_MAX_VARYING_FLOATS"; break;
    case GL_MAX_VARYING_VECTORS: value = "GL_MAX_VARYING_VECTORS"; break;
    case GL_MAX_VERTEX_ATOMIC_COUNTERS: value = "GL_MAX_VERTEX_ATOMIC_COUNTERS"; break;
    case GL_MAX_VERTEX_ATTRIBS: value = "GL_MAX_VERTEX_ATTRIBS"; break;
    case GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS: value = "GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS"; break;
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: value = "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS"; break;
    case GL_MAX_VERTEX_UNIFORM_COMPONENTS: value = "GL_MAX_VERTEX_UNIFORM_COMPONENTS"; break;
    case GL_MAX_VERTEX_UNIFORM_VECTORS: value = "GL_MAX_VERTEX_UNIFORM_VECTORS"; break;
    case GL_MAX_VERTEX_OUTPUT_COMPONENTS: value = "GL_MAX_VERTEX_OUTPUT_COMPONENTS"; break;
    case GL_MAX_VERTEX_UNIFORM_BLOCKS: value = "GL_MAX_VERTEX_UNIFORM_BLOCKS"; break;
    case GL_MAX_VIEWPORT_DIMS: value = "GL_MAX_VIEWPORT_DIMS"; break;
    case GL_MAX_VIEWPORTS: value = "GL_MAX_VIEWPORTS"; break;
    case GL_MINOR_VERSION: value = "GL_MINOR_VERSION"; break;
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS: value = "GL_NUM_COMPRESSED_TEXTURE_FORMATS"; break;
    case GL_NUM_EXTENSIONS: value = "GL_NUM_EXTENSIONS"; break;
    case GL_NUM_PROGRAM_BINARY_FORMATS: value = "GL_NUM_PROGRAM_BINARY_FORMATS"; break;
    case GL_NUM_SHADER_BINARY_FORMATS: value = "GL_NUM_SHADER_BINARY_FORMATS"; break;
    case GL_PACK_ALIGNMENT: value = "GL_PACK_ALIGNMENT"; break;
    case GL_PACK_IMAGE_HEIGHT: value = "GL_PACK_IMAGE_HEIGHT"; break;
    case GL_PACK_LSB_FIRST: value = "GL_PACK_LSB_FIRST"; break;
    case GL_PACK_ROW_LENGTH: value = "GL_PACK_ROW_LENGTH"; break;
    case GL_PACK_SKIP_IMAGES: value = "GL_PACK_SKIP_IMAGES"; break;
    case GL_PACK_SKIP_PIXELS: value = "GL_PACK_SKIP_PIXELS"; break;
    case GL_PACK_SKIP_ROWS: value = "GL_PACK_SKIP_ROWS"; break;
    case GL_PACK_SWAP_BYTES: value = "GL_PACK_SWAP_BYTES"; break;
    case GL_PIXEL_PACK_BUFFER_BINDING: value = "GL_PIXEL_PACK_BUFFER_BINDING"; break;
    case GL_PIXEL_UNPACK_BUFFER_BINDING: value = "GL_PIXEL_UNPACK_BUFFER_BINDING"; break;
    case GL_POINT_FADE_THRESHOLD_SIZE: value = "GL_POINT_FADE_THRESHOLD_SIZE"; break;
    case GL_PRIMITIVE_RESTART_INDEX: value = "GL_PRIMITIVE_RESTART_INDEX"; break;
    case GL_PROGRAM_BINARY_FORMATS: value = "GL_PROGRAM_BINARY_FORMATS"; break;
    case GL_PROGRAM_PIPELINE_BINDING: value = "GL_PROGRAM_PIPELINE_BINDING"; break;
    case GL_PROGRAM_POINT_SIZE: value = "GL_PROGRAM_POINT_SIZE"; break;
    case GL_PROVOKING_VERTEX: value = "GL_PROVOKING_VERTEX"; break;
    case GL_POINT_SIZE: value = "GL_POINT_SIZE"; break;
    case GL_POINT_SIZE_GRANULARITY: value = "GL_POINT_SIZE_GRANULARITY"; break;
    case GL_POINT_SIZE_RANGE: value = "GL_POINT_SIZE_RANGE"; break;
    case GL_POLYGON_OFFSET_FACTOR: value = "GL_POLYGON_OFFSET_FACTOR"; break;
    case GL_POLYGON_OFFSET_UNITS: value = "GL_POLYGON_OFFSET_UNITS"; break;
    case GL_POLYGON_OFFSET_FILL: value = "GL_POLYGON_OFFSET_FILL"; break;
    case GL_POLYGON_OFFSET_LINE: value = "GL_POLYGON_OFFSET_LINE"; break;
    case GL_POLYGON_OFFSET_POINT: value = "GL_POLYGON_OFFSET_POINT"; break;
    case GL_POLYGON_SMOOTH: value = "GL_POLYGON_SMOOTH"; break;
    case GL_POLYGON_SMOOTH_HINT: value = "GL_POLYGON_SMOOTH_HINT"; break;
    case GL_READ_BUFFER: value = "GL_READ_BUFFER"; break;
    case GL_RENDERBUFFER_BINDING: value = "GL_RENDERBUFFER_BINDING"; break;
    case GL_SAMPLE_BUFFERS: value = "GL_SAMPLE_BUFFERS"; break;
    case GL_SAMPLE_COVERAGE_VALUE: value = "GL_SAMPLE_COVERAGE_VALUE"; break;
    case GL_SAMPLE_COVERAGE_INVERT: value = "GL_SAMPLE_COVERAGE_INVERT"; break;
    case GL_SAMPLE_MASK_VALUE: value = "GL_SAMPLE_MASK_VALUE"; break;
    case GL_SAMPLER_BINDING: value = "GL_SAMPLER_BINDING"; break;
    case GL_SAMPLES: value = "GL_SAMPLES"; break;
    case GL_SCISSOR_BOX: value = "GL_SCISSOR_BOX"; break;
    case GL_SCISSOR_TEST: value = "GL_SCISSOR_TEST"; break;
    case GL_SHADER_COMPILER: value = "GL_SHADER_COMPILER"; break;
    case GL_SHADER_STORAGE_BUFFER_BINDING: value = "GL_SHADER_STORAGE_BUFFER_BINDING"; break;
    case GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT: value = "GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT"; break;
    case GL_SHADER_STORAGE_BUFFER_START: value = "GL_SHADER_STORAGE_BUFFER_START"; break;
    case GL_SHADER_STORAGE_BUFFER_SIZE: value = "GL_SHADER_STORAGE_BUFFER_SIZE"; break;
    case GL_SMOOTH_LINE_WIDTH_RANGE: value = "GL_SMOOTH_LINE_WIDTH_RANGE"; break;
    case GL_SMOOTH_LINE_WIDTH_GRANULARITY: value = "GL_SMOOTH_LINE_WIDTH_GRANULARITY"; break;
    case GL_STENCIL_BACK_FAIL: value = "GL_STENCIL_BACK_FAIL"; break;
    case GL_STENCIL_BACK_FUNC: value = "GL_STENCIL_BACK_FUNC"; break;
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL: value = "GL_STENCIL_BACK_PASS_DEPTH_FAIL"; break;
    case GL_STENCIL_BACK_PASS_DEPTH_PASS: value = "GL_STENCIL_BACK_PASS_DEPTH_PASS"; break;
    case GL_STENCIL_BACK_REF: value = "GL_STENCIL_BACK_REF"; break;
    case GL_STENCIL_BACK_VALUE_MASK: value = "GL_STENCIL_BACK_VALUE_MASK"; break;
    case GL_STENCIL_BACK_WRITEMASK: value = "GL_STENCIL_BACK_WRITEMASK"; break;
    case GL_STENCIL_CLEAR_VALUE: value = "GL_STENCIL_CLEAR_VALUE"; break;
    case GL_STENCIL_FAIL: value = "GL_STENCIL_FAIL"; break;
    case GL_STENCIL_FUNC: value = "GL_STENCIL_FUNC"; break;
    case GL_STENCIL_PASS_DEPTH_FAIL: value = "GL_STENCIL_PASS_DEPTH_FAIL"; break;
    case GL_STENCIL_PASS_DEPTH_PASS: value = "GL_STENCIL_PASS_DEPTH_PASS"; break;
    case GL_STENCIL_REF: value = "GL_STENCIL_REF"; break;
    case GL_STENCIL_TEST: value = "GL_STENCIL_TEST"; break;
    case GL_STENCIL_VALUE_MASK: value = "GL_STENCIL_VALUE_MASK"; break;
    case GL_STENCIL_WRITEMASK: value = "GL_STENCIL_WRITEMASK"; break;
    case GL_STEREO: value = "GL_STEREO"; break;
    case GL_SUBPIXEL_BITS: value = "GL_SUBPIXEL_BITS"; break;
    case GL_TEXTURE_BINDING_1D: value = "GL_TEXTURE_BINDING_1D"; break;
    case GL_TEXTURE_BINDING_1D_ARRAY: value = "GL_TEXTURE_BINDING_1D_ARRAY"; break;
    case GL_TEXTURE_BINDING_2D: value = "GL_TEXTURE_BINDING_2D"; break;
    case GL_TEXTURE_BINDING_2D_ARRAY: value = "GL_TEXTURE_BINDING_2D_ARRAY"; break;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE: value = "GL_TEXTURE_BINDING_2D_MULTISAMPLE"; break;
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY: value = "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY"; break;
    case GL_TEXTURE_BINDING_3D: value = "GL_TEXTURE_BINDING_3D"; break;
    case GL_TEXTURE_BINDING_BUFFER: value = "GL_TEXTURE_BINDING_BUFFER"; break;
    case GL_TEXTURE_BINDING_CUBE_MAP: value = "GL_TEXTURE_BINDING_CUBE_MAP"; break;
    case GL_TEXTURE_BINDING_RECTANGLE: value = "GL_TEXTURE_BINDING_RECTANGLE"; break;
    case GL_TEXTURE_COMPRESSION_HINT: value = "GL_TEXTURE_COMPRESSION_HINT"; break;
    case GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT: value = "GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT"; break;
    case GL_TIMESTAMP: value = "GL_TIMESTAMP"; break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING: value = "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING"; break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_START: value = "GL_TRANSFORM_FEEDBACK_BUFFER_START"; break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE: value = "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE"; break;
    case GL_UNIFORM_BUFFER_BINDING: value = "GL_UNIFORM_BUFFER_BINDING"; break;
    case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT: value = "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT"; break;
    case GL_UNIFORM_BUFFER_SIZE: value = "GL_UNIFORM_BUFFER_SIZE"; break;
    case GL_UNIFORM_BUFFER_START: value = "GL_UNIFORM_BUFFER_START"; break;
    case GL_UNPACK_ALIGNMENT: value = "GL_UNPACK_ALIGNMENT"; break;
    case GL_UNPACK_IMAGE_HEIGHT: value = "GL_UNPACK_IMAGE_HEIGHT"; break;
    case GL_UNPACK_LSB_FIRST: value = "GL_UNPACK_LSB_FIRST"; break;
    case GL_UNPACK_ROW_LENGTH: value = "GL_UNPACK_ROW_LENGTH"; break;
    case GL_UNPACK_SKIP_IMAGES: value = "GL_UNPACK_SKIP_IMAGES"; break;
    case GL_UNPACK_SKIP_PIXELS: value = "GL_UNPACK_SKIP_PIXELS"; break;
    case GL_UNPACK_SKIP_ROWS: value = "GL_UNPACK_SKIP_ROWS"; break;
    case GL_UNPACK_SWAP_BYTES: value = "GL_UNPACK_SWAP_BYTES"; break;
    case GL_VERTEX_ARRAY_BINDING: value = "GL_VERTEX_ARRAY_BINDING"; break;
    case GL_VERTEX_BINDING_DIVISOR: value = "GL_VERTEX_BINDING_DIVISOR"; break;
    case GL_VERTEX_BINDING_OFFSET: value = "GL_VERTEX_BINDING_OFFSET"; break;
    case GL_VERTEX_BINDING_STRIDE: value = "GL_VERTEX_BINDING_STRIDE"; break;
    case GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET: value = "GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET"; break;
    case GL_MAX_VERTEX_ATTRIB_BINDINGS: value = "GL_MAX_VERTEX_ATTRIB_BINDINGS"; break;
    case GL_VIEWPORT: value = "GL_VIEWPORT"; break;
    case GL_VIEWPORT_BOUNDS_RANGE: value = "GL_VIEWPORT_BOUNDS_RANGE"; break;
    case GL_VIEWPORT_INDEX_PROVOKING_VERTEX: value = "GL_VIEWPORT_INDEX_PROVOKING_VERTEX"; break;
    case GL_VIEWPORT_SUBPIXEL_BITS: value = "GL_VIEWPORT_SUBPIXEL_BITS"; break;
    case GL_MAX_ELEMENT_INDEX: value = "GL_MAX_ELEMENT_INDEX"; break;
    default: value = fmt::format("{}", name);
    }
    // clang-format on
    return value;
}
