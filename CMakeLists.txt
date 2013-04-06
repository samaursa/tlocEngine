cmake_minimum_required(VERSION 2.6)

project(tlocEngine)

set(TLOC_ENGINE_VERSION 0.1)

# Common configuration file that sets up platform and compiler specific details
include(tlocCommon.cmake)

#------------------------------------------------------------------------------
# Subdirectories

message("")
add_subdirectory(src)

#------------------------------------------------------------------------------
# CACHE Variables

set(TLOC_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "The root folder of this repository. You do not need to edit this manually")
set(TLOC_DEP_PATH "FIXME!" CACHE PATH "The tloc dependency REPOSITORY path goes here. Make sure that you have run CMake on the repository.")
set(TLOC_DEP_BUILD_PATH "FIXME!" CACHE PATH "The tloc dependency BUILD path goes here. Make sure that you have run CMake on the repository.")
