/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 ****************************************************************************/

#include "2d/CCCameraBackgroundBrush.h"
#include "2d/CCCamera.h"
#include "base/CCConsole.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

CameraBackgroundBrush::CameraBackgroundBrush()
: _glProgramState(nullptr)
{
    
}

CameraBackgroundBrush::~CameraBackgroundBrush()
{
    CC_SAFE_RELEASE(_glProgramState);
}

CameraBackgroundBrush* CameraBackgroundBrush::createNoneBrush()
{
    auto ret = new (std::nothrow) CameraBackgroundBrush();
    ret->init();
    
    ret->autorelease();
    return ret;
}

CameraBackgroundColorBrush* CameraBackgroundBrush::createColorBrush(const Color4F& color, float depth)
{
    return CameraBackgroundColorBrush::create(color, depth);
}

CameraBackgroundDepthBrush* CameraBackgroundBrush::createDepthBrush(float depth)
{
    return CameraBackgroundDepthBrush::create(depth);
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundDepthBrush::CameraBackgroundDepthBrush()
: _depth(0.f)
, _clearColor(GL_FALSE)
, _vao(0)
, _vertexBuffer(0)
, _indexBuffer(0)
{
    
}
CameraBackgroundDepthBrush::~CameraBackgroundDepthBrush()
{
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
    
    _vertexBuffer = 0;
    _indexBuffer = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
}

CameraBackgroundDepthBrush* CameraBackgroundDepthBrush::create(float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundDepthBrush();
    
    if (nullptr != ret && ret->init())
    {
        ret->_depth = depth;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool CameraBackgroundDepthBrush::init()
{
    auto shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_CAMERA_CLEAR);
    _glProgramState = GLProgramState::getOrCreateWithGLProgram(shader);
    _glProgramState->retain();
    
    _quad.bl.vertices = Vec3(-1,-1,0);
    _quad.br.vertices = Vec3(1,-1,0);
    _quad.tl.vertices = Vec3(-1,1,0);
    _quad.tr.vertices = Vec3(1,1,0);
    
    _quad.bl.colors = _quad.br.colors = _quad.tl.colors = _quad.tr.colors = Color4B(0,0,0,1);
    
    _quad.bl.texCoords = Tex2F(0,0);
    _quad.br.texCoords = Tex2F(1,0);
    _quad.tl.texCoords = Tex2F(0,1);
    _quad.tr.texCoords = Tex2F(1,1);
    
    auto supportVAO = Configuration::getInstance()->supportsShareableVAO();
    if (supportVAO)
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quad), &_quad, GL_STATIC_DRAW);
    
    GLshort indices[6] = {0, 1, 2, 3, 2, 1};
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    if (supportVAO)
    {
        // vertices
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof( V3F_C4B_T2F, vertices));

        // colors
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof( V3F_C4B_T2F, colors));

        // tex coords
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof( V3F_C4B_T2F, texCoords));
    }

    if (supportVAO)
        GL::bindVAO(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}

void CameraBackgroundDepthBrush::drawBackground(Camera* /*camera*/)
{
    GLboolean oldDepthTest;
    GLint oldDepthFunc;
    GLboolean oldDepthMask;
    {
        glColorMask(_clearColor, _clearColor, _clearColor, _clearColor);
        glStencilMask(0);
        
        oldDepthTest = glIsEnabled(GL_DEPTH_TEST);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthMask);
        
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }
    
    //draw
    
    _glProgramState->setUniformFloat("depth", _depth);
    _glProgramState->apply(Mat4::IDENTITY);
    
    auto supportVAO = Configuration::getInstance()->supportsShareableVAO();
    if (supportVAO)
        GL::bindVAO(_vao);
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, vertices));
        
        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, colors));
        
        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, texCoords));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    
    if (supportVAO)
        GL::bindVAO(0);
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    
    {
        if(GL_FALSE == oldDepthTest)
        {
            glDisable(GL_DEPTH_TEST);
        }
        glDepthFunc(oldDepthFunc);
        
        if(GL_FALSE == oldDepthMask)
        {
            glDepthMask(GL_FALSE);
        }
        
        /* IMPORTANT: We only need to update the states that are not restored.
         Since we don't know what was the previous value of the mask, we update the RenderState
         after setting it.
         The other values don't need to be updated since they were restored to their original values
         */
        glStencilMask(0xFFFFF);
        //        RenderState::StateBlock::_defaultState->setStencilWrite(0xFFFFF);
        
        /* BUG: RenderState does not support glColorMask yet. */
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundColorBrush::CameraBackgroundColorBrush()
: _color(0.f, 0.f, 0.f, 0.f)
{
    
}

CameraBackgroundColorBrush::~CameraBackgroundColorBrush()
{
    
}

bool CameraBackgroundColorBrush::init()
{
    CameraBackgroundDepthBrush::init();
    this->_clearColor = GL_TRUE;
    return true;
}

void CameraBackgroundColorBrush::drawBackground(Camera* camera)
{
    GL::blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED.src, BlendFunc::ALPHA_NON_PREMULTIPLIED.dst);

    CameraBackgroundDepthBrush::drawBackground(camera);
}

void CameraBackgroundColorBrush::setColor(const Color4F& color)
{
    _quad.bl.colors = _quad.br.colors = _quad.tl.colors = _quad.tr.colors = Color4B(color);
    
    if (_vertexBuffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quad), &_quad, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

CameraBackgroundColorBrush* CameraBackgroundColorBrush::create(const Color4F& color, float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundColorBrush();

    if (nullptr != ret && ret->init())
    {
        ret->setColor(color);
        ret->setDepth(depth);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

NS_CC_END
