#------------------------------------------------------------------------------
# Platform

set(TLOC_CURRENT_PLATFORM ${CMAKE_SYSTEM_NAME})
message(STATUS "PLATFORM: ${TLOC_CURRENT_PLATFORM}")

if(${TLOC_CURRENT_PLATFORM} STREQUAL "Windows")
  set(TLOC_PLATFORM_WIN32 1)
elseif(${TLOC_CURRENT_PLATFORM} STREQUAL "Darwin")
  # Assume iOS directly - later we will allow switchin between iOS and OSX
  set(TLOC_PLATFORM_IOS 1)
  set(CMAKE_SYSTEM_NAME iOS)
  set(CMAKE_OSX_SYSROOT iphoneos)
else()
  message("PLATFORM: Unsupported!")
  set(TLOC_PLATFORM_UNSUPPORTED 1)
endif()

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "ARCHITECTURE: x64")
  set(ARCH_DIR "x64")
else()
  message(STATUS "ARCHITECTURE: x32")
  set(ARCH_DIR "x86")
endif()

#------------------------------------------------------------------------------
# Compiler

set(TLOC_COMPILER_C11 1)

if(MSVC)
  message(STATUS "COMPILER: MSVC")
  set(TLOC_COMPILER_MSVC 1)
  if(MSVC90 OR MSVC80 OR MSVC71 OR MSVC70 OR MSVC60)
    message(STATUS "C++11: Not supported")
    set(TLOC_COMPILER_C11 0)
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC)
  message(STATUS "COMPILER: GCC Variant")
  set(TLOC_COMPILER_GCC 1)
else()
  message("COMPILER: Unsupported!")
  set(TLOC_COMPILER_UNSUPPORTED 1)
endif()

# Configurations
if(CMAKE_CXX_FLAGS_DEBUG)
  set(TLOC_CONFIG_DEBUG 1)
elseif(CMAKE_CXX_FLAGS_RELEASE)
  set(TLOC_CONFIG_RELEASE 1)
elseif(CMAKE_CXX_FLAGS_RELWITHDEBINFO)
  set(TLOC_CONFIG_RELWITHDEBINFO 1)
else()
  message("CONFIGURATION: Unsupported configuration specified!")
endif()

#------------------------------------------------------------------------------
# Application type

if(APPLE)
  set(TLOC_APP_TYPE MACOSX_BUNDLE)
else()
  set(TLOC_APP_TYPE "")
endif()

#------------------------------------------------------------------------------
# MISC

# Solution folders for MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
