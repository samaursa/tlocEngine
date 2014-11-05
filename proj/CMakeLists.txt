cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------------
# User should NOT adjust anything beyond this point
set(TLOC_PROJECT_NAME "game" CACHE STRING "The name of your project goes here")

#--------------------------------------------------------------------------
# Project name
project(${TLOC_PROJECT_NAME})

set(internal_FIXME "FIXME!")

#------------------------------------------------------------------------------
# Install function for libraries

function(tloc_install_library target_name include_folder)
  if(DISTRIBUTION_FULL_SOURCE)
    file(WRITE ${CMAKE_BINARY_DIR}/${target_name}Copy.cmake
      "file(COPY \"${USER_PATH}/src/${target_name}/${include_folder}\" 
      DESTINATION \"${USER_INSTALL_PATH}/include/${target_name}\" 
      FILE_PERMISSIONS OWNER_READ
      FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.cpp\"
      )")
  else()
    file(WRITE ${CMAKE_BINARY_DIR}/${target_name}Copy.cmake
      "file(COPY \"${USER_PATH}/src/${target_name}/${include_folder}\" 
      DESTINATION \"${USER_INSTALL_PATH}/include/${target_name}\" 
      FILE_PERMISSIONS OWNER_READ
      FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.opt.inl.h\" EXCLUDE
      )")
  endif()

  add_custom_command(TARGET ${target_name} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_BINARY_DIR}/${target_name}Copy.cmake")
endfunction()

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_ENGINE_INSTALL_PATH ${internal_FIXME} CACHE PATH "The engine INSTALL path with the correct build folder.")
set(TLOC_DEP_INSTALL_PATH ${internal_FIXME} CACHE PATH "The dependency INSTALL path with the correct build folder.")

set(USER_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "Root folder of this project. You do not need to change this path.")
set(USER_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the binaries")
set(USER_IOS_PLIST_PATH "" CACHE FILE "If you have your own custom plist, specify here. If blank, 2LoC will generate one for you.")

set(USER_ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets" CACHE PATH "You can specify your custom assets path here. NOTE: In Distribution build, the assets from this folder are copied to be relative to the binary files.")

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
# Include the common platform settings file
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_INSTALL_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#------------------------------------------------------------------------------
# Over-ride the project name with the correct suffix (iff user hasn't modified
# it already)
tloc_get_leaf_folder_name(${CMAKE_BINARY_DIR} TLOC_BUILD_FOLDER_NAME)
if(${TLOC_PROJECT_NAME} STREQUAL "game")
  set(TLOC_PROJECT_NAME "game_${TLOC_BUILD_FOLDER_NAME}" CACHE STRING "You may change the name based on build configurations" FORCE)
  project(${TLOC_PROJECT_NAME})
endif()

if(${USER_INSTALL_PATH} STREQUAL "${CMAKE_SOURCE_DIR}/INSTALL")
  set(USER_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine" FORCE)
endif()

#--------------------------------------------------------------------------
# User adjustable variables
include(tlocUserVars.cmake)

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

foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string (TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${USER_INSTALL_PATH}/lib/${CMAKE_CFG_INTDIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${USER_INSTALL_PATH}/lib/${CMAKE_CFG_INTDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${USER_INSTALL_PATH}/bin/${CMAKE_CFG_INTDIR})
endforeach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})

#--------------------------------------------------------------------------
# The src folder MUST exist
add_subdirectory(src)
