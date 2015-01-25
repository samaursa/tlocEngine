set(TLOC_PREFAB 
  tlocPrefabBase.h 
  tlocPrefabBase.cpp
  tloc_prefab.cpp 
  tloc_prefab.h 
  tloc_prefab.inl.h 
  )

set(TLOC_PREFAB_CORE
  core/tloc_core.cpp 
  core/tloc_core.h 
  core/tloc_core.inl.h 
  core/tlocUserData.h
  core/tlocUserData.cpp
  )

set(TLOC_PREFAB_GRAPHICS
  graphics/tlocArcBall.h
  graphics/tlocArcBall.cpp
  graphics/tlocBoundingBox.h
  graphics/tlocBoundingBox.cpp
  graphics/tlocCamera.cpp 
  graphics/tlocCamera.h 
  graphics/tlocCuboid.h
  graphics/tlocCuboid.cpp
  graphics/tlocDynamicText.h
  graphics/tlocDynamicText.cpp
  graphics/tlocFan.cpp 
  graphics/tlocFan.h 
  graphics/tlocMaterial.h
  graphics/tlocMaterial.cpp
  graphics/tlocMesh.h
  graphics/tlocMesh.cpp
  graphics/tlocQuad.cpp 
  graphics/tlocQuad.h 
  graphics/tlocRaypick.h
  graphics/tlocRaypick.cpp
  graphics/tlocSceneNode.h
  graphics/tlocSceneNode.cpp
  graphics/tlocSprite.h
  graphics/tlocSprite.cpp
  graphics/tlocStaticText.h
  graphics/tlocStaticText.cpp
  graphics/tlocTextureCoords.h
  graphics/tlocTextureCoords.cpp
  graphics/tloc_graphics.cpp 
  graphics/tloc_graphics.h 
  graphics/tloc_graphics.inl.h 
  )

set(TLOC_PREFAB_INPUT
  input/tloc_input.cpp 
  input/tloc_input.h 
  input/tloc_input.inl.h 
  input/tlocArcBallControl.h
  input/tlocArcBallControl.cpp
  )

set(TLOC_PREFAB_MATH
  math/tloc_math.cpp 
  math/tloc_math.h 
  math/tloc_math.inl.h
  math/tlocTransform.h
  math/tlocTransform.cpp
  )

set(TLOC_PREFAB_PHYSICS
  physics/tlocRigidBody.cpp 
  physics/tlocRigidBody.h 
  physics/tloc_physics.cpp 
  physics/tloc_physics.h 
  physics/tloc_physics.inl.h
  )

set(TLOC_PREFAB_ANIMATION
  animation/tloc_animation.h
  animation/tloc_animation.inl.h
  animation/tloc_animation.cpp
  animation/tlocTransformAnimation.h
  animation/tlocTransformAnimation.cpp
  )

#-------------------------------------------
# Project setup

include_directories(
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  )

add_library(tlocPrefab STATIC
  ${TLOC_PREFAB}
  ${TLOC_PREFAB_CORE}
  ${TLOC_PREFAB_GRAPHICS}
  ${TLOC_PREFAB_INPUT}
  ${TLOC_PREFAB_MATH}
  ${TLOC_PREFAB_PHYSICS}
  ${TLOC_PREFAB_ANIMATION}
  )

add_dependencies(tlocPrefab
  tlocCore
  tlocGraphics
  tlocInput
  tlocMath
  tlocPhysics
  tlocPrefab
  )

set_platform_specific_properties(tlocPrefab)

# Filters to organize the source files
source_group(core             FILES ${TLOC_PREFAB_CORE})
source_group(graphics         FILES ${TLOC_PREFAB_GRAPHICS})
source_group(input            FILES ${TLOC_PREFAB_INPUT})
source_group(math             FILES ${TLOC_PREFAB_MATH})
source_group(physics          FILES ${TLOC_PREFAB_PHYSICS})
source_group(animation        FILES ${TLOC_PREFAB_ANIMATION})

tloc_install_library(tlocPrefab "")
