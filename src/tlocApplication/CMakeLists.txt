set(TLOC_ANIMATION
  tlocApplicationBase.h 
  tlocApplicationBase.cpp
  tloc_application.cpp 
  tloc_application.h 
  tloc_application.inl.h 

  tlocApplication.h
  tlocApplication.cpp
  )

#-------------------------------------------
# Project setup

include_directories(
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  )

add_library(tlocApplication STATIC
  ${TLOC_ANIMATION}
  )

add_dependencies(tlocApplication
  tlocCore
  tlocGraphics
  tlocInput
  tlocMath
  tlocPhysics
  tlocPrefab
  )

set_platform_specific_properties(tlocApplication)

# Filters to organize the source files
# source_group(core             FILES ${TLOC_PREFAB_CORE})

tloc_install_library(tlocApplication "")
