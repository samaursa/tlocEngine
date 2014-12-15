cmake_minimum_required(VERSION 2.6)

set(TLOC_PROJECT_NAME "tlocEngine" CACHE STRING "You may change the name based on build configuration")

#--------------------------------------------------------------------------
# Project name
project(${TLOC_PROJECT_NAME})

set(internal_FIXME "FIXME!")

#------------------------------------------------------------------------------
# Install function for libraries

function(tloc_install_library target_name include_folder)
  if(DISTRIBUTION_FULL_SOURCE)
    file(WRITE ${CMAKE_BINARY_DIR}/${target_name}Copy.cmake
      "file(COPY \"${TLOC_ENGINE_PATH}/src/${include_folder}\" 
      DESTINATION \"${TLOC_ENGINE_INSTALL_PATH}/include/\" 
      FILE_PERMISSIONS OWNER_READ
      FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.cpp\"
      )")
  else()
    file(WRITE ${CMAKE_BINARY_DIR}/${target_name}Copy.cmake
      "file(COPY \"${TLOC_ENGINE_PATH}/src/${include_folder}\" 
      DESTINATION \"${TLOC_ENGINE_INSTALL_PATH}/include/\" 
      FILE_PERMISSIONS OWNER_READ
      FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.opt.inl.h\" EXCLUDE
      )")
  endif()

  add_custom_command(TARGET ${target_name} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_BINARY_DIR}/${target_name}Copy.cmake")
endfunction()

function(tloc_check_paths path_list)
  foreach(PATHDIR ${path_list})
    if (${${PATHDIR}} MATCHES ${internal_FIXME})
      message(FATAL_ERROR "Please enter a path for ${PATHDIR}")
    endif()
  endforeach()
endfunction()

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_DEP_INSTALL_PATH ${internal_FIXME} CACHE PATH "The tloc dependency INSTALL path goes here.")
set(TLOC_ENGINE_INSTALL_PATH ${internal_FIXME} CACHE PATH "Install directory for the engine")

#------------------------------------------------------------------------------
# Common configuration file that sets up platform and compiler specific details
tloc_check_paths(${TLOC_DEP_INSTALL_PATH})
set(TLOC_COMMON_CMAKE_PATH "${TLOC_DEP_INSTALL_PATH}/tlocCommon.cmake")
include(${TLOC_COMMON_CMAKE_PATH})

#--------------------------------------------------------------------------
# User adjustable variables
include(tlocUserVars.cmake)

tloc_check_paths(${TLOC_CHECK_PATHS})

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

#------------------------------------------------------------------------------
# Subdirectories

message("")
add_subdirectory(src)
