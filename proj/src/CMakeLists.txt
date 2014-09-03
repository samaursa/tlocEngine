# -----------------------------------------------------------------------------
# Functions

function(add_common_libraries EXEC_NAME)
  target_link_libraries(${EXEC_NAME}
    tlocCore
    tlocGraphics
    tlocMath
    tlocInput
    tlocPhysics
    tlocPrefab
    tlocAnimation
    FreeType
    Box2D
    )

  if (TLOC_PLATFORM_WIN32)

    # Add OpenGL libraries for Windows
    target_link_libraries(${EXEC_NAME}
      glu32.lib
      OpenGL32.lib
      dinput8.lib
      )

  endif()

  if(TLOC_COMPILER_XCODE)
  endif()

endfunction()

function(add_apple_plist EXEC_NAME ASSETS_PATH)
  if(TLOC_PLATFORM_IOS)
    # Check if a PLIST file was specified. If not, then go with default.
    if(USER_IOS_PLIST_PATH)
      set(PLIST_PATH ${USER_IOS_PLIST_PATH})
    else()
      set(PLIST_PATH "${TLOC_ENGINE_INSTALL_PATH}/platform/iOS/tlocEngine.plist")
    endif()

    set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}" PARENT_SCOPE)
    set(PRODUCT_NAME    "\${PRODUCT_NAME}" PARENT_SCOPE)
    set(BUNDLE_NAME     ${EXEC_NAME} PARENT_SCOPE)
    set_target_properties(${EXEC_NAME} PROPERTIES 
		MACOSX_BUNDLE_INFO_PLIST ${PLIST_PATH})
    set_target_properties(${EXEC_NAME} PROPERTIES
    		RESOURCE "${ASSETS_PATH}")
  endif()
endfunction()

# -----------------------------------------------------------------------------
# compiler flags

tloc_add_definitions_strict()

# common includes
include_directories(
  ${TLOC_ENGINE_INSTALL_PATH}/
  ${TLOC_ENGINE_INSTALL_PATH}/include/
  ${TLOC_DEP_INSTALL_PATH}/include/
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  ${TLOC_DEP_INSTALL_PATH}/include/CATCH/
  ${USER_PATH}/src/

  ${CMAKE_SOURCE_DIR}/src/
  )

# common link directories
link_directories(
  ${TLOC_ENGINE_INSTALL_PATH}/lib/
  ${TLOC_DEP_INSTALL_PATH}/lib/
  )

# -----------------------------------------------------------------------------
# Add all libraries and executables

message("")
message(STATUS "-- Libraries --")
foreach(lib ${USER_LIBRARY_PROJECTS})
  message(STATUS "Adding ${lib} library project")
  set(USER_CURRENT_PROJECT_TYPE ${USER_PROJECT_TYPE_LIB})
  set(USER_CURRENT_PROJECT_NAME ${lib})

  add_subdirectory(${lib})

  # put the libraries in the "Libraries" folder
  set_target_properties(${lib} 
    PROPERTIES
    FOLDER Libraries
    )
endforeach()
message(STATUS "-- Libraries -- DONE") 

message("")
message(STATUS "-- Executables --")
foreach(exec ${USER_EXECUTABLE_PROJECTS})
  message(STATUS "Adding ${exec} executable project")
  set(USER_CURRENT_PROJECT_TYPE ${USER_PROJECT_TYPE_EXE})
  set(USER_CURRENT_PROJECT_NAME ${exec})
  
  add_subdirectory(${exec})

  # put the executable in the "Projects" folder
  set_target_properties(${exec} 
    PROPERTIES
    FOLDER Projects
    )
endforeach()
message(STATUS "-- Executables -- DONE")

# -----------------------------------------------------------------------------
# compiler flags
#
# NOTE: For tests we need regular compiler flags which enable RTTI and 
#       exceptions

tloc_add_definitions()

# -----------------------------------------------------------------------------
# Add all test executables

message("")
message(STATUS "-- Tests --")
foreach(test ${USER_TEST_PROJECTS})
  message(STATUS "Adding ${test} executable project")
  set(USER_CURRENT_PROJECT_TYPE ${USER_PROJECT_TYPE_EXE})
  set(USER_CURRENT_PROJECT_NAME ${test})

# test projects require exceptions and rtti to be enabled - build fails in xcode only
if(TLOC_COMPILER_XCODE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_DEFAULT} -DTLOC_DEBUG -std=c++11 -stdlib=libc++ -Wno-unused-function -g")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_DEFAULT} -DTLOC_RELEASE -std=c++11 -stdlib=libc++ -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT} -DTLOC_RELEASE_DEBUGINFO -std=c++11 -stdlib=libc++ -Wno-unused-function -g")
endif()
  
  add_subdirectory(${test})

  # put the executable in the "Tests" folder
  set_target_properties(${test} 
    PROPERTIES
    FOLDER Tests 
    )
endforeach()
message(STATUS "-- Tests -- DONE")

# -----------------------------------------------------------------------------
# Generate tlocAssetPath.h file
FILE(WRITE ${USER_ASSETS_PATH} "
#pragma once

#ifndef _ASSETS_PATH_H_
#define _ASSETS_PATH_H_

#include <cstring>

#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#define TLOC_ASSETS_PATH \"${CMAKE_SOURCE_DIR}/assets/\"

#if defined(TLOC_OS_WIN)

inline const char* GetAssetsPath()
{
  static const char* assetPath = \"${CMAKE_SOURCE_DIR}/assets/\";
  return assetPath;
}
#elif defined(TLOC_OS_IPHONE)
inline const char* GetAssetsPath()
{
  static char assetPath[1024];
  strcpy(assetPath, [[[NSBundle mainBundle] resourcePath]
                     cStringUsingEncoding:[NSString defaultCStringEncoding]]);
  strcat(assetPath, \"/assets/\");

  return assetPath;
}
#endif

#endif // _ASSETS_PATH_H_

")

