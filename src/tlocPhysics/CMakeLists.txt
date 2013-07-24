set(TLOC_PHYSICS
  tlocDepVersionCheck.cpp 
  tlocPhysicsBase.h 
  tloc_physics.cpp 
  tloc_physics.h 
  tloc_physics.inl.h
  )

set(TLOC_PHYSICS_BOX2D 
  box2d/tlocPhysicsManager.cpp 
  box2d/tlocPhysicsManager.h 
  box2d/tlocRigidBody.cpp 
  box2d/tlocRigidBody.h 
  box2d/tlocRigidBody.inl.h 
  box2d/tlocRigidBodyDef.cpp 
  box2d/tlocRigidBodyDef.h 
  box2d/tlocRigidBodyShapeDef.cpp 
  box2d/tlocRigidBodyShapeDef.h 
  box2d/tlocWorld.cpp 
  box2d/tlocWorld.h 
  box2d/tloc_box2d.cpp 
  box2d/tloc_box2d.h 
  box2d/tloc_box2d.inl.h
  )

set(TLOC_PHYSICS_COMPONENT_SYSTEM 
  component_system/tlocComponentType.h 
  component_system/tlocRigidBodyComponent.cpp 
  component_system/tlocRigidBodyComponent.h 
  component_system/tlocRigidBodyListenerComponent.cpp 
  component_system/tlocRigidbodyListenerComponent.h 
  component_system/tlocRigidBodyListenerSystem.cpp 
  component_system/tlocRigidBodyListenerSystem.h 
  component_system/tlocRigidBodyShapeComponent.cpp 
  component_system/tlocRigidBodyShapeComponent.h 
  component_system/tlocRigidBodySystem.cpp 
  component_system/tlocRigidBodySystem.h 
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl.h
  )

set(TLOC_PHYSICS_ERROR 
  error/tlocErrorTypes.h 
  error/tloc_error.cpp 
  error/tloc_error.h 
  error/tloc_error.inl.h
  )

#-------------------------------------------
# Project setup

add_definitions(-DGLEW_STATIC)

include_directories(
  ${TLOC_ENGINE_PATH}/src/3rdParty/
  ${TLOC_DEP_PATH}/include/Box2D/
)

add_library(tlocPhysics STATIC
  ${TLOC_PHYSICS}
  ${TLOC_PHYSICS_BOX2D}
  ${TLOC_PHYSICS_COMPONENT_SYSTEM}
  ${TLOC_PHYSICS_ERROR}
  )

add_dependencies(tlocPhysics
  tlocCore
  tlocMath
  )

# Filters to organize the source files
source_group(box2d            FILES ${TLOC_PHYSICS_BOX2D})
source_group(component_system FILES ${TLOC_PHYSICS_COMPONENT_SYSTEM})
source_group(error            FILES ${TLOC_PHYSICS_ERROR})
