# Remove MINSIZERE
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Define TLOC_CXX03 if C++11 is NOT supported (force XCode to C++03 for now)
if(NOT TLOC_COMPILER_C11 OR TLOC_COMPILER_XCODE)
  add_definitions(-DTLOC_CXX03)
endif()

# Backup the default flags
SET(CMAKE_CXX_FLAGS_DEFAULT                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_DEFAULT           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_DEFAULT         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

if(TLOC_COMPILER_MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG           "/DTLOC_DEBUG /Od /Gm /RTC1 /MTd /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELEASE         "/DTLOC_RELEASE /O2 /Ob2 /Oi /Ot /GL /MT /Gy /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/DTLOC_RELEASE_DEBUGINFO /O2 /Ob2 /Oi /Ot /Gm /MT /Gy /GR- /W4 /WX /c /Zi /TP")

  #turn off exceptions for all configurations
  string(REGEX REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE "/Zm1000" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REGEX REPLACE "/GX" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
elseif(TLOC_COMPILER_XCODE)
  # Note that -gdwarf-2 generates debug symbols (dsym files in dwarf standard)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTLOC_DEBUG -fno-exceptions -fno-rtti -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DTLOC_RELEASE -fno-exceptions -fno-rtti -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DTLOC_RELEASE_DEBUGINFO -fno-exceptions -fno-rtti -Wno-unused-function")
  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework OpenGLES -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenAL")

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework OpenGLES -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenAL")
else()
  message("Configuration not applied because compiler is unsupported (or not detected properly)")
endif()

# common includes
include_directories(
  ${TLOC_DEP_PATH}/include/
  ${TLOC_DEP_PATH}/src/
  ${TLOC_PATH}/src/
  )

# All libraries/projects add their name to this variable
set(tlocAllLibraries 
  tlocCore 
  tlocGraphics 
  tlocInput 
  tlocMath 
  tlocPhysics 
  tlocPrefab
  )

foreach(lib ${tlocAllLibraries})
  add_subdirectory(${lib})
endforeach()

# Add the tests directory which contains all test projects
add_subdirectory(tlocTests)

# Add the version tool - currently DISABLED for APPLE due to iOS builds
if(NOT TLOC_PLATFORM_IOS)
  add_subdirectory(tlocVersion)

  # Make tlocVersion and tlocVersionTool as dependencies for all projects
  foreach(lib ${tlocAllLibraries})
    add_dependencies(${lib}
      tlocVersion
      tlocVersionTool
      )
  endforeach()

endif()

# this is so far required only by MSVC
if(TLOC_COMPILER_MSVC)
  foreach(lib ${tlocAllLibraries})
    if(TARGET ${lib})
      set_target_properties(${lib} 
        PROPERTIES
        FOLDER tlocEngine
        )
    else()
      message("Library ${lib} was not generated successfully.")
    endif()
  endforeach()

#The version tools must be added to the engine folder as well
set_target_properties(tlocVersion tlocVersionTool
  PROPERTIES
  FOLDER Versioning
  )

endif()

# -----------------------------------------------------------------------------
# Generate tlocAssetPath.h file
FILE(WRITE "${CMAKE_SOURCE_DIR}/src/tlocAssetsPath.h" "
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
