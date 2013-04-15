#------------------------------------------------------------------------------
# This file is included AFTER CMake adds the executable/library
# Do NOT remove the following variables. Modify the variables to suit your 
# project.

# Do NOT remove the following variables. Modify the variables to suit your project
set(USER_SOURCE_FILES
  src/skopworksLogo.h
  src/skopworksLogo.cpp
  )

# Do not include individual assets here. Only add paths
set(USER_ASSETS_PATH
  ../../assets
  )

# Dependent project is compiled after dependency
set(USER_PROJECT_DEPENDENCIES
  " "
  )

# Libraries that the executable needs to link against
set(USER_EXECUTABLE_LINK_LIBRARIES
  " "
  )
