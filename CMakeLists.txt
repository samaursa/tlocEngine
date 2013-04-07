cmake_minimum_required(VERSION 2.6)

project(tlocEngine)

set(TLOC_ENGINE_VERSION 0.1)

set(internal_FIXME "FIXME!")

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "The root folder of this repository. You do not need to edit this manually")
set(TLOC_DEP_PATH ${internal_FIXME} CACHE PATH "The tloc dependency REPOSITORY path goes here. Make sure that you have run CMake on the repository.")
set(TLOC_DEP_BUILD_PATH ${internal_FIXME} CACHE PATH "The tloc dependency BUILD path goes here. Make sure that you have run CMake on the repository.")

# Variables to check for ${internal_FIXEM}
set(TLOC_CHECK_PATHS
  TLOC_PATH
  TLOC_DEP_PATH
  TLOC_DEP_BUILD_PATH
  )

foreach(PATHDIR ${TLOC_CHECK_PATHS})
  if (${${PATHDIR}} MATCHES ${internal_FIXME})
    message(FATAL_ERROR "Please enter a path for ${PATHDIR}")
  endif()
endforeach()

# Common configuration file that sets up platform and compiler specific details
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#------------------------------------------------------------------------------
# Subdirectories

message("")
add_subdirectory(src)
