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

# build engine library and all tests

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(Cocos2d-x VERSION 3.17)

set(COCOS2DX_ROOT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/NewModules)
include(${PROJECT_SOURCE_DIR}/cmake/Modules/CocosCompileOptions.cmake)

find_package(Freetype REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(cereal REQUIRED)
find_package(WebP REQUIRED)
find_package(xxhash REQUIRED)
find_package(Libwebsockets REQUIRED)

find_package(JPEG)
find_package(PNG)
find_package(TIFF)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/unzip)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/xxtea)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/clipper)

add_subdirectory(${PROJECT_SOURCE_DIR}/cocos)
#add_subdirectory(${COCOS2DX_ROOT_PATH}/tests ${ENGINE_BINARY_PATH}/tests)
