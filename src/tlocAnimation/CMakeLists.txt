set(TLOC_ANIMATION
  tlocDepVersionCheck.cpp 
  tlocAnimationBase.h
  tlocAnimationBase.cpp
  tloc_animation.cpp 
  tloc_animation.h 
  tloc_animation.inl.h 
  )

set(TLOC_ANIMATION_COMPONENT_SYSTEM
  component_system/tlocComponentType.h
  component_system/tlocTransformAnimation.h
  component_system/tlocTransformAnimation.cpp
  component_system/tlocTransformAnimationSystem.h
  component_system/tlocTransformAnimationSystem.cpp
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl.h
  )

set(TLOC_GRAPHICS_ERROR 
  error/tlocErrorTypes.h 
  error/tloc_error.cpp 
  error/tloc_error.h 
  error/tloc_error.inl.h
  )

set(TLOC_GRAPHICS_TYPES 
  types/tlocKeyframe.h 
  types/tlocKeyframe.inl.h
  types/tlocKeyframe.cpp 
  types/tloc_types.cpp 
  types/tloc_types.h 
  types/tloc_types.inl.h
  )

#-------------------------------------------
# Project setup

add_library(tlocAnimation STATIC
  ${TLOC_ANIMATION}
  ${TLOC_ANIMATION_COMPONENT_SYSTEM}
  ${TLOC_GRAPHICS_ERROR}
  ${TLOC_GRAPHICS_TYPES}
  )

add_dependencies(tlocAnimation
  tlocCore
  tlocMath
  )

set_platform_specific_properties(tlocAnimation)

# Filters to organize the source files
source_group(component_system FILES ${TLOC_ANIMATION_COMPONENT_SYSTEM})
source_group(error            FILES ${TLOC_ANIMATION_ERROR})
source_group(types            FILES ${TLOC_ANIMATION_TYPES})
