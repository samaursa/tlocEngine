# add strict compiler flags
tloc_add_definitions_strict()

# common includes
include_directories(
  ${TLOC_DEP_INSTALL_PATH}
  ${TLOC_DEP_INSTALL_PATH}/include/
  ${TLOC_ENGINE_PATH}/src/
  )

# All libraries/projects add their name to this variable
set(tlocAllLibraries 
  tlocCore 
  tlocGraphics 
  tlocInput 
  tlocMath 
  tlocPhysics 
  tlocPrefab
  tlocAnimation
  )

foreach(lib ${tlocAllLibraries})
  add_subdirectory(${lib})
endforeach()

# Add the tests directory which contains all test projects
if (TLOC_INCLUDE_TESTS)
  add_subdirectory(tlocTests)
endif()

# Add the version tool - currently DISABLED for APPLE due to iOS builds
if(NOT TLOC_PLATFORM_IOS AND NOT TLOC_ENGINE_DISTRIBUTION_BUILD)
  add_subdirectory(tlocVersion)

  # Make tlocVersion and tlocVersionTool as dependencies for all projects
  foreach(lib ${tlocAllLibraries})
    add_dependencies(${lib}
      tlocVersion
      tlocVersionTool
      )
  endforeach()

  #The version tools must be added to the engine folder as well
  set_target_properties(tlocVersion tlocVersionTool
    PROPERTIES
    FOLDER Versioning
    )

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

endif()

# -----------------------------------------------------------------------------
# Generate tlocAssetPath.h file

if(NOT TLOC_ENGINE_DISTRIBUTION_BUILD)
  SET(ENGINE_ASSETS_PATH ${CMAKE_SOURCE_DIR}/assets/)
else()
  SET(ENGINE_ASSETS_PATH "../../assets/")

  file(COPY ${TLOC_ENGINE_PATH}/assets
    DESTINATION ${TLOC_ENGINE_INSTALL_PATH}/
    FILES_MATCHING PATTERN "*.*"
    )
endif()

FILE(WRITE "${CMAKE_SOURCE_DIR}/src/tlocAssetsPath.h" "
#pragma once

#ifndef _ASSETS_PATH_H_
#define _ASSETS_PATH_H_

#include <cstring>

#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#define TLOC_ASSETS_PATH \"${ENGINE_ASSETS_PATH}\"

#if defined(TLOC_OS_WIN)

inline const char* GetAssetsPath()
{
  static const char* assetPath = \"${ENGINE_ASSETS_PATH}\";
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
