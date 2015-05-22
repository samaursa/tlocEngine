set(TLOC_ENGINE_APPLICATION
  tlocApplicationBase.h 
  tlocApplicationBase.cpp
  tloc_application.cpp 
  tloc_application.h 
  tloc_application.inl.h 

  tlocApplication.h
  tlocApplication.cpp
  )
set(TLOC_ENGINE_APPLICATION_RESOURCES
    resources/tloc_resources.h
    resources/tloc_resources.inl.h
    resources/tloc_resources.opt.inl.h
    resources/tloc_resources.cpp
    resources/tlocResource.h
    resources/tlocResource.cpp
    resources/tlocResourceFactory.h
    resources/tlocResourceFactory.inl.h
    resources/tlocResourceFactory.cpp
)

#-------------------------------------------
# Project setup

include_directories(
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  )

add_library(tlocApplication STATIC
  ${TLOC_ENGINE_APPLICATION}
  ${TLOC_ENGINE_APPLICATION_RESOURCES}
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
source_group(resources             FILES ${TLOC_ENGINE_APPLICATION_RESOURCES})

tloc_install_library(tlocApplication "")
