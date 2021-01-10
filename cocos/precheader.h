// precompiled header
// include here heavy headers which are included in many files
// this will speed-up build a lot
#pragma once

// types
#include <limits>
#include <string>
#include <cctype>
#include <sstream>

// containers
#include <iterator>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>

// utilities
#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include <functional>
#include <algorithm>
#include <utility>
#include <tuple>

// cocos
/*
#include "base/ccConfig.h"

// base
#include "base/CCAsyncTaskPool.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCConfiguration.h"
#include "base/CCData.h"
#include "base/CCDirector.h"
#include "base/CCIMEDelegate.h"
#include "base/CCIMEDispatcher.h"
#include "base/CCProperties.h"
#include "base/CCRef.h"
#include "base/CCRefPtr.h"
#include "base/CCScheduler.h"
#include "base/CCValue.h"
#include "base/CCVector.h"
#include "base/base64.h"
#include "base/ccConfig.h"
#include "base/ccMacros.h"
#include "base/ccTypes.h"
#include "base/ccUTF8.h"
#include "base/ccUtils.h"

// EventDispatcher
#include "base/CCEventCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventFocus.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCInputEvents.h"
#include "base/CCEventController.h"
#include "base/CCController.h"
#include "base/CCEventType.h"

// math
#include "math/CCAffineTransform.h"
#include "math/CCGeometry.h"
#include "math/CCVertex.h"
#include "math/Mat4.h"
#include "math/MathUtil.h"
#include "math/Quaternion.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

// actions
#include "2d/CCAction.h"
#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionManager.h"
#include "2d/CCTweenFunction.h"

// 2d nodes
#include "2d/CCAtlasNode.h"
#include "2d/CCClippingNode.h"
#include "2d/CCDrawNode.h"
#include "2d/CCLabel.h"
#include "2d/CCLayer.h"
#include "2d/CCNode.h"
#include "2d/CCParticleBatchNode.h"
#include "2d/CCParticleSystem.h"
#include "2d/CCParticleSystemQuad.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCScene.h"

// 2d utils
#include "2d/CCCamera.h"

// include
#include "base/CCProtocols.h"

// renderer
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCPass.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCRenderCommandPool.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCFrameBuffer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/ccShaders.h"

// platform
#include "platform/CCCommon.h"
#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCSAXParser.h"
#include "platform/CCThread.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "platform/win32/CCApplication-win32.h"
    #include "platform/desktop/CCGLViewImpl-desktop.h"
    #include "platform/win32/CCGL-win32.h"
    #include "platform/win32/CCStdC-win32.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    #include "platform/desktop/CCGLViewImpl-desktop.h"
    #include "platform/mac/CCApplication-mac.h"
    #include "platform/mac/CCGL-mac.h"
    #include "platform/mac/CCStdC-mac.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    #include "platform/linux/CCApplication-linux.h"
    #include "platform/desktop/CCGLViewImpl-desktop.h"
    #include "platform/linux/CCGL-linux.h"
    #include "platform/linux/CCStdC-linux.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

// sprite_nodes
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"

// text_input_node
#include "2d/CCTextFieldTTF.h"

// textures
#include "renderer/CCTextureAtlas.h"

// tilemap_parallax_nodes
#include "2d/CCTMXObjectGroup.h"
#include "2d/CCTMXXMLParser.h"
#include "2d/CCFastTMXLayer.h"
#include "2d/CCFastTMXTiledMap.h"
*/
