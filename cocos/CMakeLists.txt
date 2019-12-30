#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

# this CMakeLists is to generate Cocos2d-x Engine Library
# build libcocos2d

include(2d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(math/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(base/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(audio/CMakeLists.txt)

add_library(cocos2d STATIC
    cocos2d.h
    cocos2d.cpp
    ${COCOS_2D_HEADER}
    ${COCOS_PLATFORM_HEADER}
    ${COCOS_PHYSICS_HEADER}
    ${COCOS_MATH_HEADER}
    ${COCOS_RENDERER_HEADER}
    ${COCOS_BASE_HEADER}
    ${COCOS_AUDIO_HEADER}
    ${COCOS_UI_HEADER}
    ${COCOS_EXTENSIONS_HEADER}
    ${COCOS_2D_SRC}
    ${COCOS_PLATFORM_SRC}
    ${COCOS_PHYSICS_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_AUDIO_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_EXTENSIONS_SRC}
)

add_library(cocos2d::cocos2d ALIAS cocos2d)

# C++11 and PIC
target_compile_features(cocos2d PUBLIC cxx_std_11 c_std_99)
set_target_properties(cocos2d PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

# Include Interface
target_include_directories(cocos2d
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/extensions
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${COCOS_PLATFORM_INCLUDE_PATHS}
)

# Dependencies
target_link_libraries(cocos2d
    PUBLIC
        glfw

    PRIVATE
        # optional dependencies
        $<$<BOOL:${BUILD_JPEG_SUPPORT}>:JPEG::JPEG>
        $<$<BOOL:${BUILD_PNG_SUPPORT}>:PNG::PNG>
        $<$<BOOL:${BUILD_TIFF_SUPPORT}>:TIFF::TIFF>
        $<$<BOOL:${USE_SYSTEM_MINIZIP}>:MINIZIP::minizip>

        # dependencies
        OpenAL::AL
        OpenGL::GL
        GLEW::GLEW
        Freetype::Freetype
        tinyxml2::tinyxml2
        RapidJSON::RapidJSON
        xxhash::xxhash
        cereal
        MPG123::MPG123
        Vorbis::File

        # internal dependencies
        clipper::clipper

        # required platform dependencies
        $<$<PLATFORM_ID:Linux>:unofficial::fontconfig::fontconfig>
        $<$<PLATFORM_ID:Darwin>:Iconv::Iconv>
        $<$<PLATFORM_ID:Darwin>:AudioToolbox::AudioToolbox>
        $<$<PLATFORM_ID:Windows>:ws2_32>
        $<$<PLATFORM_ID:Windows>:winmm>
        $<$<PLATFORM_ID:Windows>:version>
)

# Definitions
target_compile_definitions(cocos2d
    PRIVATE
        CC_USE_JPEG=$<BOOL:${BUILD_JPEG_SUPPORT}>
        CC_USE_PNG=$<BOOL:${BUILD_PNG_SUPPORT}>
        CC_USE_TIFF=$<BOOL:${BUILD_TIFF_SUPPORT}>

        $<$<BOOL:${USE_SYSTEM_MINIZIP}>:MINIZIP_FROM_SYSTEM>

        $<$<PLATFORM_ID:Windows>:MPG123_DEF_SSIZE_T>
        $<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>
        $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS>

    PUBLIC
        $<$<CONFIG:Debug>:COCOS2D_DEBUG>

        $<$<PLATFORM_ID:Windows>:UNICODE>
        $<$<PLATFORM_ID:Windows>:_UNICODE>
        $<$<PLATFORM_ID:Windows>:WIN32>
        $<$<PLATFORM_ID:Windows>:_WIN32>
        $<$<PLATFORM_ID:Windows>:CC_STATIC>
        $<$<PLATFORM_ID:Windows>:COCOS2DXWIN32_EXPORTS>
        $<$<PLATFORM_ID:Darwin>:USE_FILE32API>
        $<$<PLATFORM_ID:Darwin>:TARGET_OS_MAC>
        $<$<PLATFORM_ID:Linux>:LINUX>
)

# Private Compile Options
target_compile_options(cocos2d PRIVATE
    # Enable all warnings on non-windows platforms
    $<$<NOT:$<PLATFORM_ID:Windows>>:-Wall>

    # Disable specific warnings (TODO: why?)
    $<$<PLATFORM_ID:Windows>:-wd4005>
    $<$<PLATFORM_ID:Windows>:-wd4056>
    $<$<PLATFORM_ID:Windows>:-wd4099>
    $<$<PLATFORM_ID:Windows>:-wd4244>
    $<$<PLATFORM_ID:Windows>:-wd4251>
    $<$<PLATFORM_ID:Windows>:-wd4334>
    $<$<PLATFORM_ID:Windows>:-wd4514>
    $<$<PLATFORM_ID:Windows>:-wd4710>
    $<$<PLATFORM_ID:Windows>:-wd4820>
    $<$<PLATFORM_ID:Windows>:-wd4996>

    $<$<NOT:$<PLATFORM_ID:Windows>>:-Wno-deprecated-declarations>
    $<$<NOT:$<PLATFORM_ID:Windows>>:$<$<COMPILE_LANGUAGE:CXX>:-Wno-invalid-offsetof>>
    $<$<NOT:$<PLATFORM_ID:Windows>>:$<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>>
)
