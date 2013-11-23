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
    Box2D
    )

  if (TLOC_PLATFORM_WIN32)

    # Add OpenGL libraries for Windows
    target_link_libraries(${EXEC_NAME}
      glu32.lib
      OpenGL32.lib
      )

    # Find dinput.lib and add it as a link target
    if(${ARCH_DIR} MATCHES "x86")
      find_library(DIRECT_INPUT_LIB
        NAMES dinput8.lib
        PATHS ${TLOC_DEP_PATH}/src/WinSDK/WinSDK/Win32/lib
        )
    else()
      find_library(DIRECT_INPUT_LIB
        NAMES dinput8.lib
        PATHS ${TLOC_DEP_PATH}/src/WinSDK/WinSDK/x64/lib
        )
    endif()

    target_link_libraries(${EXEC_NAME}
      ${DIRECT_INPUT_LIB}
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
      set(PLIST_PATH "${TLOC_ENGINE_PATH}/platform/iOS/tlocEngine.plist")
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

# This will load the default C++ configurations for supported compilers which enables
# RTTI, Exception handling etc.
function(load_default_configurations)
  set(CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT} PARENT_SCOPE)
  set(CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT} PARENT_SCOPE)
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT} PARENT_SCOPE)

  if(TLOC_COMPILER_MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG           "/DTLOC_DEBUG /Od /Gm  /EHsc /RTC1 /MTd /GR /W4 /WX /c /Zi /TP" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELEASE         "/DTLOC_RELEASE /O2 /Ob2 /Oi /Ot /GL /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/DTLOC_RELEASE_DEBUGINFO /O2 /Ob2 /Oi /Ot /Gm /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP" PARENT_SCOPE)
  elseif(TLOC_COMPILER_XCODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTLOC_DEBUG -std=c++11 -stdlib=libc++ -fno-rtti -Wno-unused-function -g" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DTLOC_RELEASE -std=c++11 -stdlib=libc++ -fno-rtti -Wno-unused-function" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -std=c++11 -stdlib=libc++ -DTLOC_RELEASE_DEBUGINFO -fno-rtti -Wno-unused-function -g" PARENT_SCOPE)
  else()
    message("Configuration not applied because compiler is unsupported (or not detected properly)")
  endif()
endfunction()

function(tloc_enable_exceptions)
  add_definitions(
    -DTLOC_ENABLE_CPPUNWIND 
    )
endfunction()

function(tloc_enable_rtti)
  add_definitions(
    -DTLOC_ENABLE_CPPRTTI 
    )
endfunction()

function(tloc_enable_stl)
  add_definitions(
    -DTLOC_USING_STL 
    )
endfunction()

# -----------------------------------------------------------------------------

# Remove MinSizeRel
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE)

# Define TLOC_CXX03 if C++11 is NOT supported (force XCode to C++03 for now)
if(NOT TLOC_COMPILER_C11)
  add_definitions(-DTLOC_CXX03)
endif()

# Backup the default flags
SET(CMAKE_CXX_FLAGS_DEFAULT                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_DEFAULT           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_DEFAULT         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

if(TLOC_COMPILER_MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)

  set(CMAKE_CXX_FLAGS_DEBUG           "/DTLOC_DEBUG /Od /Gm /RTC1 /MTd /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELEASE         "/DTLOC_RELEASE /O2 /Ob2 /Oi /Ot /GL /MT /Gy /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/DTLOC_RELEASE_DEBUGINFO /O2 /Ob2 /Oi /Ot /Gm /MT /Gy /GR- /W4 /WX /c /Zi /TP")

  #turn off exceptions for all configurations
  string(REGEX REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE "/Zm1000" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REGEX REPLACE "/GX" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
elseif(TLOC_COMPILER_XCODE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTLOC_DEBUG -std=c++11 -stdlib=libc++ -fno-exceptions -fno-rtti -Wno-unused-function -g")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DTLOC_RELEASE -std=c++11 -stdlib=libc++ -fno-exceptions -fno-rtti -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DTLOC_RELEASE_DEBUGINFO -std=c++11 -stdlib=libc++ -fno-exceptions -fno-rtti -Wno-unused-function -g")
  set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -stdlib=libc++ -framework Foundation -framework OpenGLES -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenAL")
else()
  message("Configuration not applied because compiler is unsupported (or not detected properly)")
endif()

# common includes
include_directories(
  ${TLOC_ENGINE_PATH}/src/
  ${TLOC_DEP_PATH}/include/
  ${TLOC_DEP_PATH}/include/Box2D/
  ${TLOC_DEP_PATH}/include/CATCH/
  ${USER_PATH}/src/

  ${CMAKE_SOURCE_DIR}/src/
  )

# common link directories
link_directories(
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocCore/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocGraphics/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocMath/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocInput/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocPhysics/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocPrefab/
  ${TLOC_ENGINE_BUILD_PATH}/src/tlocAnimation/

  ${TLOC_DEP_BUILD_PATH}/src/Box2D/
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

