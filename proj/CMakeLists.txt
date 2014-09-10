cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------------
# Project name
project(${TLOC_PROJECT_NAME})

#--------------------------------------------------------------------------
# User should NOT adjust anything beyond this point
set(TLOC_PROJECT_NAME "game" CACHE STRING "The name of your project goes here")

set(internal_FIXME "FIXME!")

#------------------------------------------------------------------------------
# Grab the build path
string(REPLACE "/" ";" p2list "${PROJECT_BINARY_DIR}")
list(REVERSE p2list)
list(GET p2list 0 USER_BUILD_FOLDER_NAME)

#------------------------------------------------------------------------------
# Install function for libraries

function(tloc_install_library target_name include_folder)
  if(USER_INCLUDE_FULL_SOURCE)
    INSTALL(DIRECTORY "${USER_PATH}/src/${target_name}/${include_folder}/" 
      DESTINATION "${USER_INSTALL_PATH}/include/${target_name}/" 
      FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp")
  else()
    INSTALL(DIRECTORY "${USER_PATH}/src/${target_name}/${include_folder}/" 
      DESTINATION "${USER_INSTALL_PATH}/include/${target_name}/" 
      FILES_MATCHING PATTERN "*.h"
      PATTERN "*.opt.inl.h" EXCLUDE)
  endif()
endfunction()

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_ENGINE_INSTALL_PATH ${internal_FIXME} CACHE PATH "The engine INSTALL path with the correct build folder.")
set(TLOC_DEP_INSTALL_PATH ${internal_FIXME} CACHE PATH "The dependency INSTALL path with the correct build folder.")

set(USER_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "Root folder of this project. You do not need to change this path.")
set(USER_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${USER_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the binaries")
set(USER_INCLUDE_FULL_SOURCE TRUE CACHE BOOL "Include full source, including opt.inl.h and .cpp files.")
set(USER_IOS_PLIST_PATH "" CACHE FILE "If you have your own custom plist, specify here. If blank, 2LoC will generate one for you.")

# Variables to check for ${internal_FIXEM}
set(TLOC_CHECK_PATHS
  TLOC_ENGINE_INSTALL_PATH
  TLOC_DEP_INSTALL_PATH
  )

foreach(PATHDIR ${TLOC_CHECK_PATHS})
  if (${${PATHDIR}} MATCHES ${internal_FIXME})
    message(FATAL_ERROR "Please enter a path for ${PATHDIR}")
  endif()
endforeach()

#--------------------------------------------------------------------------
# User adjustable variables
include(tlocUserVars.cmake)

#--------------------------------------------------------------------------
# Include the common platform settings file
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_INSTALL_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#--------------------------------------------------------------------------
# Sanity checks
list(LENGTH USER_EXECUTABLE_PROJECTS tlocExecProjLength)
list(LENGTH USER_LIBRARY_PROJECTS tlocLibProjLength)
if(${tlocExecProjLength} EQUAL 0 AND 
   ${tlocLibProjLength} EQUAL 0)
   message(SEND_ERROR "You must have at least one executable or library")
endif()

#------------------------------------------------------------------------------
# Set binary build directories

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${USER_INSTALL_PATH}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${USER_INSTALL_PATH}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${USER_INSTALL_PATH}/bin)

#--------------------------------------------------------------------------
# The src folder MUST exist
add_subdirectory(src)
