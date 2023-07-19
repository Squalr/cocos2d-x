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
option(BUILD_PNG_SUPPORT         "Build PNG Support"                 ON)

include(FetchContent)
include(ExternalProject)
set(BUILD_SHARED_LIBS OFF)

# OpenGL
if(POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE GLVND)
endif()
find_package(OpenGL REQUIRED)

# Platform dependencies
if(LINUX)
    # find_package(unofficial-fontconfig REQUIRED)
elseif(WINDOWS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(APPLE)
    find_package(Iconv REQUIRED)
endif()

# Bundled Dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/external)

# Sources
add_subdirectory(${PROJECT_SOURCE_DIR}/cocos)

# Tests
if (BUILD_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()
