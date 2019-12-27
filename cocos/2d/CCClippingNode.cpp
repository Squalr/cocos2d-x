/*
 * Copyright (c) 2012      Pierre-David Bélanger
 * Copyright (c) 2012      cocos2d-x.org
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "2d/CCClippingNode.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "base/CCDirector.h"
#include "base/CCStencilStateManager.h"

NS_CC_BEGIN

ClippingNode::ClippingNode()
: _stencil(nullptr)
, _stencilStateManager(new StencilStateManager())
, _originStencilProgram(nullptr)
{
}

ClippingNode::~ClippingNode()
{
    if (_stencil)
    {
        _stencil->stopAllActions();
        _stencil->release();
    }
    CC_SAFE_DELETE(_stencilStateManager);
}

ClippingNode* ClippingNode::create()
{
    ClippingNode *ret = new (std::nothrow) ClippingNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

ClippingNode* ClippingNode::create(Node *pStencil)
{
    ClippingNode *ret = new (std::nothrow) ClippingNode();
    if (ret && ret->init(pStencil))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool ClippingNode::init()
{
    return init(nullptr);
}

bool ClippingNode::init(Node *stencil)
{
    setStencil(stencil);
    return true;
}

void ClippingNode::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    Node::onEnter();
    
    if (_stencil != nullptr)
    {
        _stencil->onEnter();
    }
    else
    {
        CCLOG("ClippingNode warning: _stencil is nil.");
    }
}

void ClippingNode::onEnterTransitionDidFinish()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnterTransitionDidFinish))
            return;
    }
#endif
    
    Node::onEnterTransitionDidFinish();
    
    if (_stencil != nullptr)
    {
        _stencil->onEnterTransitionDidFinish();
    }
}

void ClippingNode::onExitTransitionDidStart()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExitTransitionDidStart))
            return;
    }
#endif
    
    if (_stencil != nullptr)
    {
        _stencil->onExitTransitionDidStart();
    }
   
    Node::onExitTransitionDidStart();
}

void ClippingNode::onExit()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExit))
            return;
    }
#endif
    
    if (_stencil != nullptr)
    {
        _stencil->onExit();
    }
    
    Node::onExit();
}


void ClippingNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible || !hasContent())
        return;
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    this->setContentSize(_stencil == nullptr ? Size::ZERO : _stencil->getContentSize());

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

    _beforeVisitCmd.init(_globalZOrder);
    _beforeVisitCmd.func = CC_CALLBACK_0(StencilStateManager::onBeforeVisit, _stencilStateManager);
    renderer->addCommand(&_beforeVisitCmd);
    
    _stencil->visit(renderer, _modelViewTransform, flags);

    _afterDrawStencilCmd.init(_globalZOrder);
    _afterDrawStencilCmd.func = CC_CALLBACK_0(StencilStateManager::onAfterDrawStencil, _stencilStateManager);
    renderer->addCommand(&_afterDrawStencilCmd);

    bool visibleByCamera = isVisitableByVisitingCamera();
    
    // self draw
    if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }

    for (int index = 0; index < _children.size(); index++)
    {
        _children[index]->visit(renderer, _modelViewTransform, flags);
    }

    _afterVisitCmd.init(_globalZOrder);
    _afterVisitCmd.func = CC_CALLBACK_0(StencilStateManager::onAfterVisit, _stencilStateManager);
    renderer->addCommand(&_afterVisitCmd);
}

void ClippingNode::setCameraMask(unsigned short mask, bool applyChildren)
{
    Node::setCameraMask(mask, applyChildren);
    
    if (_stencil)
        _stencil->setCameraMask(mask, applyChildren);
}

Node* ClippingNode::getStencil() const
{
    return _stencil;
}

void ClippingNode::setStencil(Node *stencil)
{
    //early out if the stencil is already set
    if (_stencil == stencil)
        return;
    
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        if (_stencil)
            sEngine->releaseScriptObject(this, _stencil);
        if (stencil)
            sEngine->retainScriptObject(this, stencil);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    
    //cleanup current stencil
    if(_stencil != nullptr && _stencil->isRunning())
    {
        _stencil->onExitTransitionDidStart();
        _stencil->onExit();
    }
    CC_SAFE_RELEASE_NULL(_stencil);
    
    //initialise new stencil
    _stencil = stencil;
    CC_SAFE_RETAIN(_stencil);
    if(_stencil != nullptr && this->isRunning())
    {
        _stencil->onEnter();
        if(this->_isTransitionFinished)
        {
            _stencil->onEnterTransitionDidFinish();
        }
    }
    
    if (_stencil != nullptr)
        _originStencilProgram = _stencil->getGLProgram();
}

bool ClippingNode::hasContent() const
{
    return _children.size() > 0;
}

GLfloat ClippingNode::getAlphaThreshold() const
{
    return _stencilStateManager->getAlphaThreshold();
}

void ClippingNode::setAlphaThreshold(GLfloat alphaThreshold)
{
    _stencilStateManager->setAlphaThreshold(alphaThreshold);
}

bool ClippingNode::isInverted() const
{
    return _stencilStateManager->isInverted();
}

void ClippingNode::setInverted(bool inverted)
{
    _stencilStateManager->setInverted(inverted);
}


NS_CC_END
