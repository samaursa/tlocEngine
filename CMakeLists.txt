cmake_minimum_required(VERSION 2.6)

set(TLOC_ENGINE_NAME "tlocEngine" CACHE STRING "You may change the name based on build configuration")

project(${TLOC_ENGINE_NAME})

set(TLOC_ENGINE_VERSION 0.1)

set(internal_FIXME "FIXME!")

#------------------------------------------------------------------------------
# Install function for libraries

function(tloc_install_library target_name include_folder)
  if(TLOC_INCLUDE_FULL_SOURCE)
    INSTALL(DIRECTORY "${TLOC_ENGINE_PATH}/src/${include_folder}" 
      DESTINATION "${TLOC_ENGINE_INSTALL_PATH}/include" 
      FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp")
  else()
    INSTALL(DIRECTORY "${TLOC_ENGINE_PATH}/src/${include_folder}" 
      DESTINATION "${TLOC_ENGINE_INSTALL_PATH}/include" 
      FILES_MATCHING PATTERN "*.h"
      PATTERN "*.opt.inl.h" EXCLUDE)
  endif()
endfunction()

#------------------------------------------------------------------------------
# Grab the build path
string(REPLACE "/" ";" p2list "${PROJECT_BINARY_DIR}")
list(REVERSE p2list)
list(GET p2list 0 TLOC_BUILD_FOLDER_NAME)

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_ENGINE_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "The root folder of this repository. You do not need to edit this manually")
set(TLOC_ENGINE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine")
set(TLOC_DEP_INSTALL_PATH ${internal_FIXME} CACHE PATH "The tloc dependency INSTALL path goes here.")
set(TLOC_INCLUDE_TESTS TRUE CACHE BOOL "Include tests in the project.")
set(TLOC_INCLUDE_FULL_SOURCE TRUE CACHE BOOL "Include full source, including opt.inl.h and .cpp files.")
set(TLOC_ENABLE_MEMORY_TRACKING TRUE CACHE BOOL "Disabling the tracker will increase debugging performance. Tracker is ALWAYS DISABLED in Release.")

# Variables to check for ${internal_FIXEM}
set(TLOC_CHECK_PATHS
  TLOC_ENGINE_PATH
  TLOC_DEP_INSTALL_PATH
  )

foreach(PATHDIR ${TLOC_CHECK_PATHS})
  if (${${PATHDIR}} MATCHES ${internal_FIXME})
    message(FATAL_ERROR "Please enter a path for ${PATHDIR}")
  endif()
endforeach()

# Common configuration file that sets up platform and compiler specific details
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_INSTALL_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#------------------------------------------------------------------------------
# Copy the platform files
file(COPY ${TLOC_ENGINE_PATH}/platform/ 
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/platform/ 
  FILES_MATCHING PATTERN "*.*"
  )

file(COPY ${TLOC_ENGINE_PATH}/src/3rdParty
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/include/
  FILES_MATCHING PATTERN "*.*"
  )

#------------------------------------------------------------------------------
# Set binary build directories

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TLOC_ENGINE_INSTALL_PATH}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TLOC_ENGINE_INSTALL_PATH}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TLOC_ENGINE_INSTALL_PATH}/bin)

#------------------------------------------------------------------------------
# Subdirectories

message("")
add_subdirectory(src)
