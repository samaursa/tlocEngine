# Remove MINSIZEREL
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# For compilers that are C++03, add the following definition
if (MSVC90 OR MSVC80 OR MSVC71 OR MSVC70 OR MSVC60)
  add_definitions(-DTLOC_CXX03)
endif()
#if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
if (APPLE)
  add_definitions(-DTLOC_CXX03)
endif()


# Common preprocessors
if(CMAKE_CXX_FLAGS_DEBUG)
  add_definitions(-DTLOC_DEBUG)
  add_definitions(-DDEBUG)
elseif(CMAKE_CXX_FLAGS_RELEASE)
  add_definitions(-DTLOC_RELEASE)
  add_definitions(-DNDEBUG)
elseif(CMAKE_CXX_FLAGS_RELWITHDEBINFO)
  add_definitions(-DTLOC_RELEASE_DEBUGINFO)
endif()

# Backup the default flags
SET(CMAKE_CXX_FLAGS_DEFAULT                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_DEFAULT           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_DEFAULT         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG           "/Od /Gm /RTC1 /MTd /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELEASE         "/O2 /Ob2 /Oi /Ot /GL /MT /Gy /GR- /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/O2 /Ob2 /Oi /Ot /Gm /MT /Gy /GR- /W4 /WX /c /Zi /TP")

  #turn off exceptions for all configurations
  string(REGEX REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE "/Zm1000" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REGEX REPLACE "/GX" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()
if(APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "-fno-exceptions -fno-rtti")
  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework OpenGLES -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenAL")
endif()

# lib/exe path for all configurations
message("${TARGET_SONAME}")
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib/${ARCH_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${ARCH_DIR})

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

# Add the version tool
add_subdirectory(tlocVersion)

# this is so far required only by MSVC
if(MSVC)
  foreach(lib ${tlocAllLibraries})
    if(TARGET ${lib})
      # Add the common linker properties to all libraries
      set_target_properties(${lib}
        PROPERTIES
        STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
        STATIC_LIBRARY_FLAGS_RELWITHDEBINFO "/LTCG"
        )
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
  FOLDER tlocEngine/Versioning
  )

endif()

# Generate tlocAssetPath.h file
FILE(WRITE ${CMAKE_SOURCE_DIR}/src/tlocAssetsPath.h "
#define TLOC_ASSETS_PATH \"${CMAKE_SOURCE_DIR}/assets/\"
")
