#------------------------------------------------------------------------------
# CACHED Variables setup

if(${TLOC_ENGINE_INSTALL_PATH} STREQUAL ${internal_FIXME})
  set(TLOC_ENGINE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine" FORCE)
endif()
set(TLOC_ENGINE_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "The root folder of this repository. You do not need to edit this manually")
set(TLOC_INCLUDE_TESTS TRUE CACHE BOOL "Include tests in the project.")

#------------------------------------------------------------------------------
# Variables to check for ${internal_FIXEM}
set(TLOC_CHECK_PATHS
    ${TLOC_CHECK_PATHS}
    TLOC_ENGINE_PATH
    TLOC_DEP_INSTALL_PATH
  )

#------------------------------------------------------------------------------
# Over-ride the project name with the correct suffix (iff user hasn't modified
# it already)
tloc_get_leaf_folder_name(${CMAKE_BINARY_DIR} TLOC_BUILD_FOLDER_NAME)
if(${TLOC_PROJECT_NAME} STREQUAL "tlocEngine")
  set(TLOC_PROJECT_NAME "tlocEngine_${TLOC_BUILD_FOLDER_NAME}" CACHE STRING "You may change the name based on build configurations" FORCE)
  project(${TLOC_PROJECT_NAME})
endif()

if(${TLOC_ENGINE_INSTALL_PATH} STREQUAL "${CMAKE_SOURCE_DIR}/INSTALL")
  set(TLOC_ENGINE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine" FORCE)
endif()

set(USER_INSTALL_PATH ${TLOC_ENGINE_INSTALL_PATH})

#------------------------------------------------------------------------------
# Copy the platform files
file(COPY ${TLOC_ENGINE_PATH}/platform/ 
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/platform/ 
  FILES_MATCHING PATTERN "*.*"
  )

#------------------------------------------------------------------------------
# Copy other source files

file(COPY ${TLOC_ENGINE_PATH}/src/tlocTests
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/include/
  FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp"
  )

#------------------------------------------------------------------------------
# Copy the license file

file(COPY ${TLOC_ENGINE_PATH}/LICENSE.pdf
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/)

#------------------------------------------------------------------------------
# Projects in this solution


set(USER_EXECUTABLE_PROJECTS ";")
#list(APPEND USER_EXECUTABLE_PROJECTS "nextExeProject;")

set(USER_LIBRARY_PROJECTS "tlocCore;")
list(APPEND USER_LIBRARY_PROJECTS "tlocMath;")
list(APPEND USER_LIBRARY_PROJECTS "tlocInput;")
list(APPEND USER_LIBRARY_PROJECTS "tlocGraphics;")
list(APPEND USER_LIBRARY_PROJECTS "tlocPhysics;")
list(APPEND USER_LIBRARY_PROJECTS "tlocPrefab;")
list(APPEND USER_LIBRARY_PROJECTS "tlocAnimation;")

set(USER_TEST_PROJECTS "tlocCoreTests;")
list(APPEND USER_TEST_PROJECTS "tlocMathTests;")
list(APPEND USER_TEST_PROJECTS "tlocInputTests;")
list(APPEND USER_TEST_PROJECTS "tlocGraphicsTests;")
list(APPEND USER_TEST_PROJECTS "tlocPhysicsTests;")
list(APPEND USER_TEST_PROJECTS "tlocPrefabTests;")
list(APPEND USER_TEST_PROJECTS "tlocAnimationTests;")
