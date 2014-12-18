#------------------------------------------------------------------------------
# CACHED Variables setup

if(${TLOC_ENGINE_INSTALL_PATH} STREQUAL ${internal_FIXME})
  set(TLOC_ENGINE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine" FORCE)
endif()

#------------------------------------------------------------------------------
# Over-ride the project name with the correct suffix (iff user hasn't modified
# it already)
tloc_get_leaf_folder_name(${CMAKE_BINARY_DIR} TLOC_BUILD_FOLDER_NAME)
if(${TLOC_SOLUTION_NAME} STREQUAL "solution")
  set(TLOC_SOLUTION_NAME "tlocEngine_${TLOC_BUILD_FOLDER_NAME}" CACHE STRING "You may change the name based on build configurations" FORCE)
  project(${TLOC_SOLUTION_NAME})
endif()

if(${TLOC_ENGINE_INSTALL_PATH} STREQUAL "${CMAKE_SOURCE_DIR}/INSTALL")
  set(TLOC_ENGINE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/INSTALL/${TLOC_BUILD_FOLDER_NAME}" CACHE PATH "Install directory for the engine" FORCE)
endif()

set(USER_INSTALL_PATH ${TLOC_ENGINE_INSTALL_PATH})

#------------------------------------------------------------------------------
# Copy the platform files
file(COPY ${SOLUTION_PATH}/platform/ 
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/platform/ 
  FILES_MATCHING PATTERN "*.*"
  )

#------------------------------------------------------------------------------
# Copy other source files

file(COPY ${SOLUTION_PATH}/src/tlocTests
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/include/
  FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp"
  )

#------------------------------------------------------------------------------
# Copy the license file

file(COPY ${SOLUTION_PATH}/LICENSE.pdf
  DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/)

#------------------------------------------------------------------------------
# Projects in this solution


set(SOLUTION_EXECUTABLE_PROJECTS "")

set(SOLUTION_LIBRARY_PROJECTS "tlocCore;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocMath;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocInput;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocGraphics;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocPhysics;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocPrefab;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "tlocAnimation;")
list(APPEND SOLUTION_LIBRARY_PROJECTS "3rdParty;")

set(SOLUTION_TEST_PROJECTS "tlocCoreTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocMathTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocInputTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocGraphicsTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocPhysicsTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocPrefabTests;")
list(APPEND SOLUTION_TEST_PROJECTS "tlocAnimationTests;")
