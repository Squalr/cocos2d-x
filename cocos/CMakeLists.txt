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

if(WINDOWS)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

include(2d/CMakeLists.txt)
include(3d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(physics3d/CMakeLists.txt)
include(math/CMakeLists.txt)
include(navmesh/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(vr/CMakeLists.txt)
include(base/CMakeLists.txt)
include(deprecated/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(network/CMakeLists.txt)
include(audio/CMakeLists.txt)
include(storage/CMakeLists.txt)

if(BUILD_EDITOR_COCOSBUILDER)
    include(editor-support/cocosbuilder/CMakeLists.txt)
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CCB_SRC} ${COCOS_CCB_HEADER})
endif(BUILD_EDITOR_COCOSBUILDER)

if(BUILD_EDITOR_COCOSTUDIO)
    include(editor-support/cocostudio/CMakeLists.txt)
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CS_SRC} ${COCOS_CS_HEADER})
endif(BUILD_EDITOR_COCOSTUDIO)

if(BUILD_EDITOR_SPINE)
    include(editor-support/spine/CMakeLists.txt)
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_SPINE_SRC} ${COCOS_SPINE_HEADER})
endif(BUILD_EDITOR_SPINE)

if(BUILD_EXTENSIONS)
    include(../extensions/CMakeLists.txt)
endif(BUILD_EXTENSIONS)

add_library(cocos2d STATIC
    cocos2d.h
    cocos2d.cpp
    ${COCOS_2D_HEADER}
    ${COCOS_3D_HEADER}
    ${COCOS_PLATFORM_HEADER}
    ${COCOS_PHYSICS_HEADER}
    ${COCOS_PHYSICS3D_HEADER}
    ${COCOS_MATH_HEADER}
    ${COCOS_NAVMESH_HEADER}
    ${COCOS_RENDERER_HEADER}
    ${COCOS_VR_HEADER}
    ${COCOS_BASE_HEADER}
    ${COCOS_AUDIO_HEADER}
    ${COCOS_UI_HEADER}
    ${COCOS_DEPRECATED_HEADER}
    ${COCOS_NETWORK_HEADER}
    ${COCOS_EDITOR_SUPPORT_HEADER}
    ${COCOS_EXTENSIONS_HEADER}
    ${COCOS_STORAGE_HEADER}
    ${COCOS_2D_SRC}
    ${COCOS_3D_SRC}
    ${COCOS_PLATFORM_SRC}
    ${COCOS_PHYSICS_SRC}
    ${COCOS_PHYSICS3D_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_NAVMESH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_VR_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_AUDIO_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_DEPRECATED_SRC}
    ${COCOS_NETWORK_SRC}
    ${COCOS_EDITOR_SUPPORT_SRC}
    ${COCOS_EXTENSIONS_SRC}
    ${COCOS_STORAGE_SRC}
)

# EVIL HACK MAKE GO AWAY
target_include_directories(cocos2d PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/extensions
    ${CMAKE_CURRENT_LIST_DIR}
)

# EVIL HACK MAKE GO AWAY
target_include_directories(cocos2d PRIVATE
    ${PROJECT_SOURCE_DIR}/external/chipmunk/include
)

target_link_libraries(cocos2d PRIVATE
    # vcpkg optional dependencies
    $<$<BOOL:JPEG_FOUND>:JPEG::JPEG>
    $<$<BOOL:PNG_FOUND>:PNG::PNG>
    $<$<BOOL:TIFF_FOUND>:TIFF::TIFF>

    # vcpkg required dependencies
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    Freetype::Freetype
    tinyxml2::tinyxml2
    xxhash::xxhash
    WebP::WebP
    GLEW::GLEW
    websockets
    cereal

    # internal dependencies
    unzip::unzip
    xxtea::xxtea
    clipper::clipper
    recast::recast

    # system dependencies
    fontconfig
    GL
    openal
    mpg123
    vorbisfile

    # fuck me
    "${PROJECT_SOURCE_DIR}/external/chipmunk/prebuilt/linux/64-bit/libchipmunk.a"
)

target_link_libraries(cocos2d PUBLIC
    glfw
)

target_compile_definitions(cocos2d PRIVATE
    CC_USE_3D_PHYSICS=0
    CC_ENABLE_BULLET_INTEGRATION=0

    $<$<BOOL:JPEG_FOUND>:CC_USE_JPEG=1>
    $<$<BOOL:PNG_FOUND>:CC_USE_PNG=1>
    $<$<BOOL:TIFF_FOUND>:CC_USE_TIFF=1>
)

if(XCODE OR VS)
    cocos_mark_code_files("cocos2d")
endif()
