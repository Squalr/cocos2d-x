/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "2d/CCParticleExamples.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"

NS_CC_BEGIN

//
// ParticleFire
//
const unsigned char __firePngData[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7A, 0x7A, 
    0xF4, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xAF, 0xC8, 0x37, 0x05, 0x8A, 
    0xE9, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66, 0x74, 0x77, 0x61, 0x72, 
    0x65, 0x00, 0x41, 0x64, 0x6F, 0x62, 0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 
    0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x02, 0x64, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 
    0xC4, 0x97, 0x89, 0x6E, 0xEB, 0x20, 0x10, 0x45, 0xBD, 0xE1, 0x2D, 0x4B, 0xFF, 0xFF, 0x37, 0x5F, 
    0x5F, 0x0C, 0xD8, 0xC4, 0xAE, 0x2D, 0xDD, 0xA9, 0x6E, 0xA7, 0x38, 0xC1, 0x91, 0xAA, 0x44, 0xBA, 
    0xCA, 0x06, 0xCC, 0x99, 0x85, 0x01, 0xE7, 0xCB, 0xB2, 0x64, 0xEF, 0x7C, 0x55, 0x2F, 0xCC, 0x69, 
    0x56, 0x15, 0xAB, 0x72, 0x68, 0x81, 0xE6, 0x55, 0xFE, 0xE8, 0x62, 0x79, 0x62, 0x04, 0x36, 0xA3, 
    0x06, 0xC0, 0x9B, 0xCA, 0x08, 0xC0, 0x7D, 0x55, 0x80, 0xA6, 0x54, 0x98, 0x67, 0x11, 0xA8, 0xA1, 
    0x86, 0x3E, 0x0B, 0x44, 0x41, 0x00, 0x33, 0x19, 0x1F, 0x21, 0x43, 0x9F, 0x5F, 0x02, 0x68, 0x49, 
    0x1D, 0x20, 0x1A, 0x82, 0x28, 0x09, 0xE0, 0x4E, 0xC6, 0x3D, 0x64, 0x57, 0x39, 0x80, 0xBA, 0xA3, 
    0x00, 0x1D, 0xD4, 0x93, 0x3A, 0xC0, 0x34, 0x0F, 0x00, 0x3C, 0x8C, 0x59, 0x4A, 0x99, 0x44, 0xCA, 
    0xA6, 0x02, 0x88, 0xC7, 0xA7, 0x55, 0x67, 0xE8, 0x44, 0x10, 0x12, 0x05, 0x0D, 0x30, 0x92, 0xE7, 
    0x52, 0x33, 0x32, 0x26, 0xC3, 0x38, 0xF7, 0x0C, 0xA0, 0x06, 0x40, 0x0F, 0xC3, 0xD7, 0x55, 0x17, 
    0x05, 0xD1, 0x92, 0x77, 0x02, 0x20, 0x85, 0xB7, 0x19, 0x18, 0x28, 0x4D, 0x05, 0x19, 0x9F, 0xA1, 
    0xF1, 0x08, 0xC0, 0x05, 0x10, 0x57, 0x7C, 0x4F, 0x01, 0x10, 0xEF, 0xC5, 0xF8, 0xAC, 0x76, 0xC8, 
    0x2E, 0x80, 0x14, 0x99, 0xE4, 0xFE, 0x44, 0x51, 0xB8, 0x52, 0x14, 0x3A, 0x32, 0x22, 0x00, 0x13, 
    0x85, 0xBF, 0x52, 0xC6, 0x05, 0x8E, 0xE5, 0x63, 0x00, 0x86, 0xB6, 0x9C, 0x86, 0x38, 0xAB, 0x54, 
    0x74, 0x18, 0x5B, 0x50, 0x58, 0x6D, 0xC4, 0xF3, 0x89, 0x6A, 0xC3, 0x61, 0x8E, 0xD9, 0x03, 0xA8, 
    0x08, 0xA0, 0x55, 0xBB, 0x40, 0x40, 0x3E, 0x00, 0xD2, 0x53, 0x47, 0x94, 0x0E, 0x38, 0xD0, 0x7A, 
    0x73, 0x64, 0x57, 0xF0, 0x16, 0xFE, 0x95, 0x82, 0x86, 0x1A, 0x4C, 0x4D, 0xE9, 0x68, 0xD5, 0xAE, 
    0xB8, 0x00, 0xE2, 0x8C, 0xDF, 0x4B, 0xE4, 0xD7, 0xC1, 0xB3, 0x4C, 0x75, 0xC2, 0x36, 0xD2, 0x3F, 
    0x2A, 0x7C, 0xF7, 0x0C, 0x50, 0x60, 0xB1, 0x4A, 0x81, 0x18, 0x88, 0xD3, 0x22, 0x75, 0xD1, 0x63, 
    0x5C, 0x80, 0xF7, 0x19, 0x15, 0xA2, 0xA5, 0xB9, 0xB5, 0x5A, 0xB7, 0xA4, 0x34, 0x7D, 0x03, 0x48, 
    0x5F, 0x17, 0x90, 0x52, 0x01, 0x19, 0x95, 0x9E, 0x1E, 0xD1, 0x30, 0x30, 0x9A, 0x21, 0xD7, 0x0D, 
    0x81, 0xB3, 0xC1, 0x92, 0x0C, 0xE7, 0xD4, 0x1B, 0xBE, 0x49, 0xF2, 0x04, 0x15, 0x2A, 0x52, 0x06, 
    0x69, 0x31, 0xCA, 0xB3, 0x22, 0x71, 0xBD, 0x1F, 0x00, 0x4B, 0x82, 0x66, 0xB5, 0xA7, 0x37, 0xCF, 
    0x6F, 0x78, 0x0F, 0xF8, 0x5D, 0xC6, 0xA4, 0xAC, 0xF7, 0x23, 0x05, 0x6C, 0xE4, 0x4E, 0xE2, 0xE3, 
    0x95, 0xB7, 0xD3, 0x40, 0xF3, 0xA5, 0x06, 0x1C, 0xFE, 0x1F, 0x09, 0x2A, 0xA8, 0xF5, 0xE6, 0x3D, 
    0x00, 0xDD, 0xAD, 0x02, 0x2D, 0xC4, 0x4D, 0x66, 0xA0, 0x6A, 0x1F, 0xD5, 0x2E, 0xF8, 0x8F, 0xFF, 
    0x2D, 0xC6, 0x4F, 0x04, 0x1E, 0x14, 0xD0, 0xAC, 0x01, 0x3C, 0xAA, 0x5C, 0x1F, 0xA9, 0x2E, 0x72, 
    0xBA, 0x49, 0xB5, 0xC7, 0xFA, 0xC0, 0x27, 0xD2, 0x62, 0x69, 0xAE, 0xA7, 0xC8, 0x04, 0xEA, 0x0F, 
    0xBF, 0x1A, 0x51, 0x50, 0x61, 0x16, 0x8F, 0x1B, 0xD5, 0x5E, 0x03, 0x75, 0x35, 0xDD, 0x09, 0x6F, 
    0x88, 0xC4, 0x0D, 0x73, 0x07, 0x82, 0x61, 0x88, 0xE8, 0x59, 0x30, 0x45, 0x8E, 0xD4, 0x7A, 0xA7, 
    0xBD, 0xDA, 0x07, 0x67, 0x81, 0x40, 0x30, 0x88, 0x55, 0xF5, 0x11, 0x05, 0xF0, 0x58, 0x94, 0x9B, 
    0x48, 0xEC, 0x60, 0xF1, 0x09, 0xC7, 0xF1, 0x66, 0xFC, 0xDF, 0x0E, 0x84, 0x7F, 0x74, 0x1C, 0x8F, 
    0x58, 0x44, 0x77, 0xAC, 0x59, 0xB5, 0xD7, 0x67, 0x00, 0x12, 0x85, 0x4F, 0x2A, 0x4E, 0x17, 0xBB, 
    0x1F, 0xC6, 0x00, 0xB8, 0x99, 0xB0, 0xE7, 0x23, 0x9D, 0xF7, 0xCF, 0x6E, 0x44, 0x83, 0x4A, 0x45, 
    0x32, 0x40, 0x86, 0x81, 0x7C, 0x8D, 0xBA, 0xAB, 0x1C, 0xA7, 0xDE, 0x09, 0x87, 0x48, 0x21, 0x26, 
    0x5F, 0x4A, 0xAD, 0xBA, 0x6E, 0x4F, 0xCA, 0xFB, 0x23, 0xB7, 0x62, 0xF7, 0xCA, 0xAD, 0x58, 0x22, 
    0xC1, 0x00, 0x47, 0x9F, 0x0B, 0x7C, 0xCA, 0x73, 0xC1, 0xDB, 0x9F, 0x8C, 0xF2, 0x17, 0x1E, 0x4E, 
    0xDF, 0xF2, 0x6C, 0xF8, 0x67, 0xAF, 0x22, 0x7B, 0xF3, 0xEB, 0x4B, 0x80, 0x01, 0x00, 0xB8, 0x21, 
    0x72, 0x89, 0x08, 0x10, 0x07, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 
    0x60, 0x82
};

static Texture2D* getDefaultTexture()
{
    Texture2D* texture = nullptr;
    Image* image = nullptr;
    do 
    {
        const std::string key = "/__firePngData";
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(key);
        CC_BREAK_IF(texture != nullptr);

        image = new (std::nothrow) Image();
        CC_BREAK_IF(nullptr == image);
        bool ret = image->initWithImageData(__firePngData, sizeof(__firePngData));
        CC_BREAK_IF(!ret);

        texture = Director::getInstance()->getTextureCache()->addImage(image, key);
    } while (0);

    CC_SAFE_RELEASE(image);

    return texture;
}

ParticleFire* ParticleFire::create()
{
    ParticleFire* ret = new (std::nothrow) ParticleFire();
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

ParticleFire* ParticleFire::createWithTotalParticles(int numberOfParticles)
{
    ParticleFire* ret = new (std::nothrow) ParticleFire();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleFire::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity.setZero();

        // Gravity Mode: radial acceleration
        this->modeA.radialAccel = 0;
        this->modeA.radialAccelVar = 0;

        // Gravity Mode: speed of particles
        this->modeA.speed = 60;
        this->modeA.speedVar = 20;        

        // starting angle
        _angle = 90;
        _angleVar = 10;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2.0f, 60.0f);
        this->_posVar.set(40.0f, 20.0f);

        // life of particles
        _life = 3;
        _lifeVar = 0.25f;


        // size, in pixels
        _startSize = 54.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.76f;
        _startColor.g = 0.25f;
        _startColor.b = 0.12f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }
        
        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleFireworks
//

ParticleFireworks* ParticleFireworks::create()
{
    ParticleFireworks* ret = new (std::nothrow) ParticleFireworks();
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

ParticleFireworks* ParticleFireworks::createWithTotalParticles(int numberOfParticles)
{
    ParticleFireworks* ret = new (std::nothrow) ParticleFireworks();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleFireworks::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration= DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity.set(0.0f, -90.0f);

        // Gravity Mode:  radial
        this->modeA.radialAccel = 0.0f;
        this->modeA.radialAccelVar = 0.0f;

        //  Gravity Mode: speed of particles
        this->modeA.speed = 180.0f;
        this->modeA.speedVar = 50.0f;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);

        // angle
        this->_angle= 90.0f;
        this->_angleVar = 20.0f;

        // life of particles
        this->_life = 3.5f;
        this->_lifeVar = 1.0f;

        // emits per frame
        this->_emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.5f;
        _startColor.g = 0.5f;
        _startColor.b = 0.5f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.1f;
        _endColor.r = 0.1f;
        _endColor.g = 0.1f;
        _endColor.b = 0.1f;
        _endColor.a = 0.2f;
        _endColorVar.r = 0.1f;
        _endColorVar.g = 0.1f;
        _endColorVar.b = 0.1f;
        _endColorVar.a = 0.2f;

        // size, in pixels
        _startSize = 8.0f;
        _startSizeVar = 2.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }
        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleSun
//
ParticleSun* ParticleSun::create()
{
    ParticleSun* ret = new (std::nothrow) ParticleSun();
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

ParticleSun* ParticleSun::createWithTotalParticles(int numberOfParticles)
{
    ParticleSun* ret = new (std::nothrow) ParticleSun();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleSun::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // additive
        this->setBlendAdditive(true);

        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity mode: speed of particles
        setSpeed(20);
        setSpeedVar(5);


        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 1;
        _lifeVar = 0.5f;

        // size, in pixels
        _startSize = 30.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per seconds
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.76f;
        _startColor.g = 0.25f;
        _startColor.b = 0.12f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        return true;
    }
    return false;
}

//
// ParticleGalaxy
//

ParticleGalaxy* ParticleGalaxy::create()
{
    ParticleGalaxy* ret = new (std::nothrow) ParticleGalaxy();
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

ParticleGalaxy* ParticleGalaxy::createWithTotalParticles(int numberOfParticles)
{
    ParticleGalaxy* ret = new (std::nothrow) ParticleGalaxy();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleGalaxy::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity Mode: speed of particles
        setSpeed(60);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-80);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(80);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 37.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.12f;
        _startColor.g = 0.25f;
        _startColor.b = 0.76f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleFlower
//

ParticleFlower* ParticleFlower::create()
{
    ParticleFlower* ret = new (std::nothrow) ParticleFlower();
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

ParticleFlower* ParticleFlower::createWithTotalParticles(int numberOfParticles)
{
    ParticleFlower* ret = new (std::nothrow) ParticleFlower();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleFlower::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity Mode: speed of particles
        setSpeed(80);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-60);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(15);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 30.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.50f;
        _startColor.g = 0.50f;
        _startColor.b = 0.50f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.5f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleMeteor
//

ParticleMeteor * ParticleMeteor::create()
{
    ParticleMeteor *ret = new (std::nothrow) ParticleMeteor();
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

ParticleMeteor* ParticleMeteor::createWithTotalParticles(int numberOfParticles)
{
    ParticleMeteor* ret = new (std::nothrow) ParticleMeteor();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleMeteor::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(-200,200));

        // Gravity Mode: speed of particles
        setSpeed(15);
        setSpeedVar(5);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 2;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 60.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.2f;
        _startColor.g = 0.4f;
        _startColor.b = 0.7f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.2f;
        _startColorVar.a = 0.1f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleSpiral
//

ParticleSpiral* ParticleSpiral::create()
{
    ParticleSpiral* ret = new (std::nothrow) ParticleSpiral();
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

ParticleSpiral* ParticleSpiral::createWithTotalParticles(int numberOfParticles)
{
    ParticleSpiral* ret = new (std::nothrow) ParticleSpiral();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleSpiral::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity Mode: speed of particles
        setSpeed(150);
        setSpeedVar(0);

        // Gravity Mode: radial
        setRadialAccel(-380);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(45);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 0;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 12;
        _lifeVar = 0;

        // size, in pixels
        _startSize = 20.0f;
        _startSizeVar = 0.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.5f;
        _startColor.g = 0.5f;
        _startColor.b = 0.5f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.5f;
        _endColor.g = 0.5f;
        _endColor.b = 0.5f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.5f;
        _endColorVar.g = 0.5f;
        _endColorVar.b = 0.5f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleExplosion
//

ParticleExplosion* ParticleExplosion::create()
{
    ParticleExplosion* ret = new (std::nothrow) ParticleExplosion();
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

ParticleExplosion* ParticleExplosion::createWithTotalParticles(int numberOfParticles)
{
    ParticleExplosion* ret = new (std::nothrow) ParticleExplosion();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleExplosion::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = 0.1f;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity Mode: speed of particles
        setSpeed(70);
        setSpeedVar(40);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life = 5.0f;
        _lifeVar = 2;

        // size, in pixels
        _startSize = 15.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_duration;

        // color of particles
        _startColor.r = 0.7f;
        _startColor.g = 0.1f;
        _startColor.b = 0.2f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.5f;
        _endColor.g = 0.5f;
        _endColor.b = 0.5f;
        _endColor.a = 0.0f;
        _endColorVar.r = 0.5f;
        _endColorVar.g = 0.5f;
        _endColorVar.b = 0.5f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSmoke
//

ParticleSmoke* ParticleSmoke::create()
{
    ParticleSmoke* ret = new (std::nothrow) ParticleSmoke();
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

ParticleSmoke* ParticleSmoke::createWithTotalParticles(int numberOfParticles)
{
    ParticleSmoke* ret = new (std::nothrow) ParticleSmoke();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleSmoke::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Emitter mode: Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,0));

        // Gravity Mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: speed of particles
        setSpeed(25);
        setSpeedVar(10);

        // angle
        _angle = 90;
        _angleVar = 5;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, 0);
        setPosVar(Vec2(20, 0));

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 60.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.8f;
        _startColor.g = 0.8f;
        _startColor.b = 0.8f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.02f;
        _startColorVar.g = 0.02f;
        _startColorVar.b = 0.02f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSnow
//

ParticleSnow* ParticleSnow::create()
{
    ParticleSnow* ret = new (std::nothrow) ParticleSnow();
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

ParticleSnow* ParticleSnow::createWithTotalParticles(int numberOfParticles)
{
    ParticleSnow* ret = new (std::nothrow) ParticleSnow();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleSnow::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = DURATION_INFINITY;

        // set gravity mode.
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0,-1));

        // Gravity Mode: speed of particles
        setSpeed(5);
        setSpeedVar(1);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height + 10);
        setPosVar(Vec2(winSize.width/2, 0));

        // angle
        _angle = -90;
        _angleVar = 5;

        // life of particles
        _life = 45;
        _lifeVar = 15;

        // size, in pixels
        _startSize = 10.0f;
        _startSizeVar = 5.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 10;

        // color of particles
        _startColor.r = 1.0f;
        _startColor.g = 1.0f;
        _startColor.b = 1.0f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 1.0f;
        _endColor.g = 1.0f;
        _endColor.b = 1.0f;
        _endColor.a = 0.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleRain
//

ParticleRain* ParticleRain::create()
{
    ParticleRain* ret = new (std::nothrow) ParticleRain();
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

ParticleRain* ParticleRain::createWithTotalParticles(int numberOfParticles)
{
    ParticleRain* ret = new (std::nothrow) ParticleRain();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticleRain::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(10,-10));

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // Gravity Mode: speed of particles
        setSpeed(130);
        setSpeedVar(30);

        // angle
        _angle = -90;
        _angleVar = 5;


        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height);
        setPosVar(Vec2(winSize.width/2, 0));

        // life of particles
        _life = 4.5f;
        _lifeVar = 0;

        // size, in pixels
        _startSize = 4.0f;
        _startSizeVar = 2.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 20;

        // color of particles
        _startColor.r = 0.7f;
        _startColor.g = 0.8f;
        _startColor.b = 1.0f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.7f;
        _endColor.g = 0.8f;
        _endColor.b = 1.0f;
        _endColor.a = 0.5f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

NS_CC_END
