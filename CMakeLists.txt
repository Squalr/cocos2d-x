#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015-2017 Chukong Technologies Inc.
# Copyright (c) 2019 Squalr
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

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(Cocos2d-x VERSION 3.17)

set(COCOS2DX_ROOT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Haven't removed all instances of these yet
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(APPLE TRUE)
    set(MACOSX TRUE)
endif()

# Options
option(BUILD_EDITOR_COCOSBUILDER "Build CocosBuilder Editor Support" OFF)
option(BUILD_EDITOR_COCOSTUDIO   "Build CocosStudio Editor Support"  OFF)
option(BUILD_EDITOR_SPINE        "Build Spine Editor Support"        OFF)
option(BUILD_EXTENSIONS          "Build ${PROJECT_NAME} Extensions"  ON)
option(BUILD_TESTS               "Build ${PROJECT_NAME} Tests"       OFF)
option(BUILD_JPEG_SUPPORT        "Build JPEG Support"                ON)
option(BUILD_PNG_SUPPORT         "Build PNG Support"                 ON)
option(BUILD_TIFF_SUPPORT        "Build TIFF Support"                ON)
option(USE_SYSTEM_MINIZIP        "Use system minizip"                OFF)

# Dependencies
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(cereal REQUIRED)
find_package(Vorbis REQUIRED)
find_package(MPG123 REQUIRED)

# Optional Dependencies
find_package(JPEG QUIET)
find_package(PNG QUIET)
find_package(TIFF QUIET)
find_package(MINIZIP QUIET)

# Platform dependencies
if(LINUX)
    find_package(unofficial-fontconfig REQUIRED)
elseif(WINDOWS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(APPLE)
    find_package(Iconv REQUIRED)
    find_package(AudioToolbox REQUIRED)
endif()

# wrap openal vars in a target
if(APPLE AND ${OPENAL_LIBRARY} MATCHES "\\.framework$")
    add_library(OpenAL::AL INTERFACE IMPORTED)
    set_target_properties(OpenAL::AL PROPERTIES
        INTERFACE_LINK_LIBRARIES ${OPENAL_LIBRARY}
    )
else()
    add_library(OpenAL::AL UNKNOWN IMPORTED)
    set_target_properties(OpenAL::AL PROPERTIES
        IMPORTED_LOCATION ${OPENAL_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${OPENAL_INCLUDE_DIR}
    )
endif()

# Validate options
if(BUILD_JPEG_SUPPORT AND NOT JPEG_FOUND)
    message(ERROR "JPEG support was requested but libjpeg wasn't found.")
endif()

if(BUILD_PNG_SUPPORT AND NOT PNG_FOUND)
    message(ERROR "PNG support was requested but libpng wasn't found.")
endif()

if(BUILD_TIFF_SUPPORT AND NOT TIFF_FOUND)
    message(ERROR "TIFF support was requested but libtiff wasn't found.")
endif()

# Bundled Dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/external)

# Sources
add_subdirectory(${PROJECT_SOURCE_DIR}/cocos)

# Tests
if (BUILD_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()
