/****************************************************************************
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
#include "base/CCEventDispatcher.h"
#include <algorithm>

#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "2d/CCScene.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

EventDispatcher::EventDispatcher()
{
    this->listenerMap = std::unordered_map<std::string, std::set<EventListenerCustom*>>();
}

EventDispatcher::~EventDispatcher()
{
    removeAllEventListeners();
}

void EventDispatcher::addEventListener(EventListenerCustom* listener)
{
    listener->retain();

    this->listenerMap[listener->getListenerID()].insert(listener);
}

void EventDispatcher::dispatchEvent(const std::string &eventName, void* optionalUserData)
{
    EventCustom event = EventCustom(eventName, optionalUserData);

    dispatchEvent(&event);
}

void EventDispatcher::dispatchEvent(EventCustom* event)
{
    const std::string& eventName = event->getEventName();

    if (this->listenerMap.find(eventName) == this->listenerMap.end())
    {
        return;
    }

    for (const auto& listener : this->listenerMap[eventName])
    {
        if (!listener->isPaused())
        {
            listener->invoke(event);
        }

        if (event->isPropagationStopped())
        {
            break;
        }
    }
}

void EventDispatcher::removeEventListener(EventListenerCustom* listener)
{
    if (listener == nullptr)
    {
        return;
    }
    
    const std::string& listenerId = listener->getListenerID();

    if (this->listenerMap[listenerId].find(listener) != this->listenerMap[listenerId].end())
    {
        listener->release();
        this->listenerMap[listenerId].erase(listener);
    }
}

void EventDispatcher::removeAllEventListeners()
{
    for (const auto& next : this->listenerMap)
    {
        for (const auto& listener : next.second)
        {
            listener->release();
        }
    }

    this->listenerMap.clear();
}

NS_CC_END
