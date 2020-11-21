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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

#include "platform/CCPlatformMacros.h"
#include "base/CCEventListener.h"
#include "base/CCEvent.h"
#include "platform/CCStdC.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class Node;
class EventCustom;
class EventListenerCustom;

/** @class EventDispatcher
* @brief This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
@js NA
*/
class CC_DLL EventDispatcher : public Ref
{
public:
    /** Constructor of EventDispatcher.
     */
    EventDispatcher();
    /** Destructor of EventDispatcher.
     */
    ~EventDispatcher();
    
    /** Adds an event listener
     */
    void addEventListener(EventListenerCustom* listener);
    
    /** Dispatches a Custom Event with a event name an optional user data.
     *
     * @param eventName The name of the event which needs to be dispatched.
     * @param optionalUserData The optional user data, it's a void*, the default value is nullptr.
     */
    void dispatchEvent(const std::string &eventName, void *optionalUserData = nullptr);
    
    /** Dispatches a Custom Event.
     *
     */
    void dispatchEvent(EventCustom* event);
    
    /** Remove a listener.
     *
     *  @param listener The specified event listener which needs to be removed.
     */
    void removeEventListener(EventListener* listener);

	/** Removes all listeners which are associated with the specified target.
	 *
	 * @param target A given target node.
	 * @param recursive True if remove recursively, the default value is false.
	 */
	void removeEventListenersForTarget(Node* target, bool recursive = false);

	/** Removes all listeners which are associated with the specified target matching the specified predicate.
	 *
	 * @param target A given target node.
	 * @param recursive True if remove recursively, the default value is false.
	 */
	void removeEventListenersForTargetWhere(Node* target, std::function<bool(EventListener*)> predicate, bool recursive = false);

    /** Removes all listeners.
     */
    void removeAllEventListeners();

    /** Pauses all listeners which are associated the specified target.
     *
     * @param target A given target node.
     * @param recursive True if pause recursively, the default value is false.
     */
    void pauseEventListenersForTarget(Node* target, bool recursive = false);
    
    /** Resumes all listeners which are associated the specified target.
     *
     * @param target A given target node.
     * @param recursive True if resume recursively, the default value is false.
     */
    void resumeEventListenersForTarget(Node* target, bool recursive = false);

    



    ///////// DEPRECATE THESE
    
    /** Adds a event listener for a specified event with the priority of scene graph.
     *  @param listener The listener of a specified event.
     *  @param node The priority of the listener is based on the draw order of this node.
     *  @note  The priority of scene graph will be fixed value 0. So the order of listener item
     *          in the vector will be ' <0, scene graph (0 priority), >0'.
     */
    void addEventListener(EventListener* listener, Node* node);
    
    /** Dispatches the event.
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     *
     * @param event The event needs to be dispatched.
     */
    // void dispatchEvent(Event* event);

    /** Dispatches a Custom Event with a event name an optional user data.
     *
     * @param eventName The name of the event which needs to be dispatched.
     * @param optionalUserData The optional user data, it's a void*, the default value is nullptr.
     */
    void dispatchCustomEvent(const std::string &eventName, void *optionalUserData = nullptr);

private:
    std::unordered_map<std::string, std::set<EventListenerCustom*>> listenerMap;

//////// OLD & DEPRECATED
    friend class Node;
    
    /** Sets the dirty flag for a node. */
    void setDirtyForNode(Node* node);
    
    /**
     *  The vector to store event listeners with scene graph based priority and fixed priority.
     */
    class EventListenerVector
    {
    public:
        EventListenerVector();
        ~EventListenerVector();
        size_t size() const;
        bool empty() const;
        
        void push_back(EventListener* item);
        void clearSceneGraphListeners();
        void clear();
        
        std::set<EventListener*>* getSceneGraphPriorityListeners() const { return _sceneGraphListeners; }
        ssize_t getGt0Index() const { return _gt0Index; }
        void setGt0Index(ssize_t index) { _gt0Index = index; }
    private:
        std::set<EventListener*>* _sceneGraphListeners;
        ssize_t _gt0Index;
    };
    
    /** Force adding an event listener
     *  @note force add an event listener which will ignore whether it's in dispatching.
     *  @see addEventListener
     */
    void forceAddEventListener(EventListener* listener);
    
    /** Gets event the listener list for the event listener type. */
    EventListenerVector* getListeners(const std::string& listenerID) const;
    
    /** Update dirty flag */
    void updateDirtyFlagForSceneGraph();
    
    /** Removes all listeners with the same event listener ID */
    void removeEventListenersForListenerID(const std::string& listenerID);
    
    /**
     *
     */
    bool removeListenerInSet(std::set<EventListener*>* listeners, EventListener* listener);
        
    void removeAllListenersInVector(std::set<EventListener*>* listenerVector);
    
    /** Sort event listener */
    void sortEventListeners(const std::string& listenerID);
    
    /** Sorts the listeners of specified type by scene graph priority */
    void sortEventListenersOfSceneGraphPriority(const std::string& listenerID, Node* rootNode);
    
    /** Updates all listeners
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     */
    void updateListeners(Event* event);
    
    /** Associates node with event listener */
    void associateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** Dissociates node with event listener */
    void dissociateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** Dispatches event to listeners with a specified listener type */
    void dispatchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /** Special version dispatchEventToListeners for touch/mouse event.
     *
     *  mouse event process flow different with common event,
     *      for scene graph node listeners, touch event process flow should
     *      order by viewport/camera first, because the touch location convert
     *      to 3D world space is different by different camera.
     *  When listener process touch event, can get current camera by Camera::getVisitingCamera().
     */
    void dispatchMouseEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    void releaseListener(EventListener* listener);
    
    /// Priority dirty flag
    enum class DirtyFlag
    {
        NONE = 0,
        SCENE_GRAPH_PRIORITY = 1 << 0,
        ALL = SCENE_GRAPH_PRIORITY
    };
    
    /** Sets the dirty flag for a specified listener ID */
    void setDirty(const std::string& listenerID, DirtyFlag flag);
    
    /** Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority */
    void visitTarget(Node* node, bool isRootNode);

    /** Remove all listeners in _toRemoveListeners list and cleanup */
    void cleanToRemovedListeners();

    /** Listeners map */
    std::unordered_map<std::string, EventListenerVector*> _listenerMap;
    
    /** The map of dirty flag */
    std::unordered_map<std::string, DirtyFlag> _priorityDirtyFlagMap;
    
    /** The map of node and event listeners */
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** The map of node and its event priority */
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** key: Global Z Order, value: Sorted Nodes */
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;
    
    /** The listeners to be added after dispatching event */
    std::vector<EventListener*> _toAddedListeners;

    /** The listeners to be removed after dispatching event */
    std::vector<EventListener*> _toRemovedListeners;

    /** The nodes were associated with scene graph based priority listeners */
    std::set<Node*> _dirtyNodes;
    
    /** Whether the dispatcher is dispatching event */
    int _inDispatch;
    
    int _nodePriorityIndex;
    
    std::set<std::string> _internalCustomListenerIDs;
};

NS_CC_END

// end of base group
/// @}

#endif // __CC_EVENT_DISPATCHER_H__
