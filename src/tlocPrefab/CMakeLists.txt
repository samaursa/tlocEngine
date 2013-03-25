set(TLOC_PREFAB 
  tlocPrefabBase.h 
  tloc_prefab.cpp 
  tloc_prefab.h 
  tloc_prefab.inl 
  )

set(TLOC_PREFAB_CORE
  core/tloc_core.cpp 
  core/tloc_core.h 
  core/tloc_core.inl 
  )

set(TLOC_PREFAB_GRAPHICS
  graphics/tlocCamera.cpp 
  graphics/tlocCamera.h 
  graphics/tlocFan.cpp 
  graphics/tlocFan.h 
  graphics/tlocQuad.cpp 
  graphics/tlocQuad.h 
  graphics/tloc_graphics.cpp 
  graphics/tloc_graphics.h 
  graphics/tloc_graphics.inl 
  )

set(TLOC_PREFAB_INPUT
  input/tloc_input.cpp 
  input/tloc_input.h 
  input/tloc_input.inl 
  )

set(TLOC_PREFAB_MATH
  math/tloc_math.cpp 
  math/tloc_math.h 
  math/tloc_math.inl 
  )

set(TLOC_PREFAB_PHYSICS
  physics/tlocRigidBody.cpp 
  physics/tlocRigidBody.h 
  physics/tloc_physics.cpp 
  physics/tloc_physics.h 
  physics/tloc_physics.inl
  )

#-------------------------------------------
# Project setup

include_directories(
  ${TLOC_DEP_PATH}/include/Box2D/
  )

add_library(tlocPrefab STATIC
  ${TLOC_PREFAB}
  ${TLOC_PREFAB_CORE}
  ${TLOC_PREFAB_GRAPHICS}
  ${TLOC_PREFAB_INPUT}
  ${TLOC_PREFAB_MATH}
  ${TLOC_PREFAB_PHYSICS}
  )

# Add to the list of all libraries
list(APPEND tlocAllLibraries tlocPrefab)

# Filters to organize the source files
source_group(core             FILES ${TLOC_PREFAB_CORE})
source_group(graphics         FILES ${TLOC_PREFAB_GRAPHICS})
source_group(input            FILES ${TLOC_PREFAB_INPUT})
source_group(math             FILES ${TLOC_PREFAB_MATH})
source_group(physics          FILES ${TLOC_PREFAB_PHYSICS})

