cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------------
# User should NOT adjust anything beyond this point
set(TLOC_PROJECT_NAME "game" CACHE STRING "The name of your project goes here")

set(internal_FIXME "FIXME!")

set(TLOC_ENGINE_PATH ${internal_FIXME} CACHE PATH "The root folder of the engine repository.")
set(TLOC_ENGINE_BUILD_PATH ${internal_FIXME} CACHE PATH "The build folder of the engine repository. Make sure the build architecture is the same.")
set(TLOC_DEP_PATH ${internal_FIXME} CACHE PATH "The tloc dependency repository path goes here. Make sure the build architecture is the same")
set(TLOC_DEP_BUILD_PATH ${internal_FIXME} CACHE PATH "The build folder of the dependency repository. Make sure the build architecture is the same")

set(USER_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "Root folder of this project. You do not need to change this path.")
set(USER_IOS_PLIST_PATH "" CACHE FILE "If you have your own custom plist, specify here. If blank, 2LoC will generate one for you.")

# Variables to check for ${internal_FIXEM}
set(TLOC_CHECK_PATHS
  TLOC_ENGINE_PATH
  TLOC_ENGINE_BUILD_PATH
  TLOC_DEP_PATH
  TLOC_DEP_BUILD_PATH
  )

foreach(PATHDIR ${TLOC_CHECK_PATHS})
  if (${${PATHDIR}} MATCHES ${internal_FIXME})
    message(FATAL_ERROR "Please enter a path for ${PATHDIR}")
  endif()
endforeach()

#--------------------------------------------------------------------------
# Project name
project(${TLOC_PROJECT_NAME})

#--------------------------------------------------------------------------
# User adjustable variables
include(tlocUserVars.cmake)

#--------------------------------------------------------------------------
# Include the common platform settings file
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#--------------------------------------------------------------------------
# Sanity checks
list(LENGTH USER_EXECUTABLE_PROJECTS tlocExecProjLength)
list(LENGTH USER_LIBRARY_PROJECTS tlocLibProjLength)
if(${tlocExecProjLength} EQUAL 0 AND 
   ${tlocLibProjLength} EQUAL 0)
   message(SEND_ERROR "You must have at least one executable or library")
endif()

#--------------------------------------------------------------------------
# Library options

# -- For now, we force the user to use all libraries
#option(TLOC_INCLUDE_CORE        "Include tlocCore"     ON)
#option(TLOC_INCLUDE_GRAPHICS    "Include tlocGraphics" ON)
#option(TLOC_INCLUDE_INPUT       "Include tlocInput"    ON)
#option(TLOC_INCLUDE_MATH        "Include tlocMath"     ON)
#option(TLOC_INCLUDE_PHYSICS     "Include tlocPhysics"  ON)
#option(TLOC_INCLUDE_PREFAB      "Include tlocPrefab"   ON)

#--------------------------------------------------------------------------
# The src folder MUST exist
add_subdirectory(src)
