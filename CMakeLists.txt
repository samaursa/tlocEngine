cmake_minimum_required(VERSION 2.6)

project(tlocEngine)

set(TLOC_ENGINE_VERSION 0.1)

set(TLOC_PLATFORM_IOS 0)
set(TLOC_PLATFORM_WIN32 0)
set(TLOC_PLATFORM_APPLE 0)

if(WIN32)
  set(TLOC_PLATFORM_WIN32 1)
elseif(APPLE)
  message(STATUS "PLATFORM: iOS")
  set(CMAKE_SYSTEM_NAME iOS)
  set(CMAKE_OSX_SYSROOT iphoneos)
  set(TLOC_PLATFORM_IOS 1)
endif()

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH_DIR "x64")
else()
  set(ARCH_DIR "x86")
endif()

add_subdirectory(src)

set(TLOC_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "The root folder of this repository. You do not need to edit this manually")
set(TLOC_DEP_PATH "FIXME!" CACHE PATH "The tloc dependency REPOSITORY path goes here. Make sure that you have run CMake on the repository.")
set(TLOC_DEP_BUILD_PATH "FIXME!" CACHE PATH "The tloc dependency BUILD path goes here. Make sure that you have run CMake on the repository.")

# Solution folders for MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
