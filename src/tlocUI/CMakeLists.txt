set(TLOC_UI
  tlocDepVersionCheck.cpp 
  tlocUIBase.h
  tlocUIBase.cpp
  tloc_ui.cpp 
  tloc_ui.h 
  tloc_ui.inl.h 
  )

set(TLOC_UI_ERROR
  error/tlocErrorTypes.h 
  error/tloc_error.cpp 
  error/tloc_error.h 
  error/tloc_error.inl.h
  )

#-------------------------------------------
# Project setup

add_library(tlocUI STATIC
  ${TLOC_UI}
  ${TLOC_UI_ERROR}
  )

add_dependencies(tlocUI
  tlocCore
  tlocGraphics
  )

set_platform_specific_properties(tlocUI)

# Filters to organize the source files
source_group(error            FILES ${TLOC_UI_ERROR})
