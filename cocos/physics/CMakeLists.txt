
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  option(FORCE_CLANG_BLOCKS "Force enable Clang blocks" YES)
endif()

if(NOT MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") # always use gnu99
  if(FORCE_CLANG_BLOCKS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks")
  endif()
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math") # extend release-profile with fast-math
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # extend debug-profile with -Wall
endif()

set(COCOS_PHYSICS_HEADER
    physics/CCPhysicsContact.h
    physics/CCPhysicsWorld.h
    physics/CCPhysicsBody.h
    physics/cpCompat62.h
    physics/CCPhysicsShape.h
    physics/CCPhysicsHelper.h
    physics/CCPhysicsJoint.h
	
	physics/chipmunk/chipmunk_structs.h
	physics/chipmunk/chipmunk_types.h
	physics/chipmunk/chipmunk_unsafe.h
	physics/chipmunk/chipmunk.h
	physics/chipmunk/cpArbiter.h
	physics/chipmunk/cpBB.h
	physics/chipmunk/cpBody.h
	physics/chipmunk/cpConstraint.h
	physics/chipmunk/cpDampedRotarySpring.h
	physics/chipmunk/cpDampedSpring.h
	physics/chipmunk/cpGearJoint.h
	physics/chipmunk/cpGrooveJoint.h
	physics/chipmunk/cpHastySpace.h
	physics/chipmunk/cpMarch.h
	physics/chipmunk/cpPinJoint.h
	physics/chipmunk/cpPivotJoint.h
	physics/chipmunk/cpPolyline.h
	physics/chipmunk/cpPolyShape.h
	physics/chipmunk/cpRatchetJoint.h
	physics/chipmunk/cpRobust.h
	physics/chipmunk/cpRotaryLimitJoint.h
	physics/chipmunk/cpShape.h
	physics/chipmunk/cpSimpleMotor.h
	physics/chipmunk/cpSlideJoint.h
	physics/chipmunk/cpSpace.h
	physics/chipmunk/cpSpatialIndex.h
	physics/chipmunk/cpTransform.h
	physics/chipmunk/cpVect.h
	physics/chipmunk/prime.h
    )

set(COCOS_PHYSICS_SRC
    physics/CCPhysicsBody.cpp
    physics/CCPhysicsContact.cpp
    physics/CCPhysicsJoint.cpp
    physics/CCPhysicsShape.cpp
    physics/CCPhysicsWorld.cpp
	
	physics/chipmunk/chipmunk.cpp
	physics/chipmunk/cpArbiter.cpp
	physics/chipmunk/cpArray.cpp
	physics/chipmunk/cpBBTree.cpp
	physics/chipmunk/cpBody.cpp
	physics/chipmunk/cpCollision.cpp
	physics/chipmunk/cpConstraint.cpp
	physics/chipmunk/cpDampedRotarySpring.cpp
	physics/chipmunk/cpDampedSpring.cpp
	physics/chipmunk/cpGearJoint.cpp
	physics/chipmunk/cpGrooveJoint.cpp
	physics/chipmunk/cpHashSet.cpp
	physics/chipmunk/cpHastySpace.cpp
	physics/chipmunk/cpMarch.cpp
	physics/chipmunk/cpPinJoint.cpp
	physics/chipmunk/cpPivotJoint.cpp
	physics/chipmunk/cpPolyline.cpp
	physics/chipmunk/cpPolyShape.cpp
	physics/chipmunk/cpRatchetJoint.cpp
	physics/chipmunk/cpRobust.cpp
	physics/chipmunk/cpRotaryLimitJoint.cpp
	physics/chipmunk/cpShape.cpp
	physics/chipmunk/cpSimpleMotor.cpp
	physics/chipmunk/cpSlideJoint.cpp
	physics/chipmunk/cpSpace.cpp
	physics/chipmunk/cpSpaceComponent.cpp
	physics/chipmunk/cpSpaceDebug.cpp
	physics/chipmunk/cpSpaceHash.cpp
	physics/chipmunk/cpSpaceQuery.cpp
	physics/chipmunk/cpSpaceStep.cpp
	physics/chipmunk/cpSpatialIndex.cpp
	physics/chipmunk/cpSweep1D.cpp
    )
