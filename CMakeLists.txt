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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/NewModules)
include(${PROJECT_SOURCE_DIR}/cmake/Modules/CocosCompileOptions.cmake)

# Options
option(BUILD_EDITOR_COCOSBUILDER "Build CocosBuilder Editor Support" OFF)
option(BUILD_EDITOR_COCOSTUDIO   "Build CocosStudio Editor Support"  OFF)
option(BUILD_EDITOR_SPINE        "Build Spine Editor Support"        OFF)
option(BUILD_EXTENSIONS          "Build ${PROJECT_NAME} Extensions"  ON)
option(BUILD_TESTS               "Build ${PROJECT_NAME} Tests"       OFF)
option(BUILD_JPEG_SUPPORT        "Build JPEG Support"                ON)
option(BUILD_PNG_SUPPORT         "Build PNG Support"                 ON)
option(BUILD_TIFF_SUPPORT        "Build TIFF Support"                ON)
option(BUILD_NETWORK_SUPPORT     "Build Network Support"             OFF)

# Dependencies
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(cereal REQUIRED)
find_package(WebP REQUIRED)
find_package(xxhash REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(Vorbis REQUIRED)
find_package(MPG123 REQUIRED)

find_package(JPEG QUIET)
find_package(PNG QUIET)
find_package(TIFF QUIET)
find_package(CURL QUIET)
find_package(OpenSSL QUIET)
find_package(Libwebsockets QUIET)

find_package(unofficial-fontconfig QUIET)

# wrap openal vars in a target
add_library(OpenAL::AL UNKNOWN IMPORTED)
set_target_properties(OpenAL::AL PROPERTIES
    IMPORTED_LOCATION ${OPENAL_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${OPENAL_INCLUDE_DIR}
)

# wrap rapidjson vars in a target
add_library(RapidJSON INTERFACE)
add_library(RapidJSON::RapidJSON ALIAS RapidJSON)
target_include_directories(RapidJSON INTERFACE ${RAPIDJSON_INCLUDE_DIRS})

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

if(BUILD_NETWORK_SUPPORT AND (NOT Libwebsockets_FOUND OR NOT OpenSSL_FOUND OR NOT CURL_FOUND))
    message(ERROR "Network support was requested but dependencies weren't found.")
endif()

if(LINUX AND NOT unofficial-fontconfig_FOUND)
    message(ERROR "Fontconfig is required on Linux, but it wasn't found.")
endif()

# Bundled Cocos (Source) Dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/external)

# Cocos Sources
add_subdirectory(${PROJECT_SOURCE_DIR}/cocos)

# Tests
if (BUILD_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()
