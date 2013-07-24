#------------------------------------------------------------------------------
# This file is included AFTER CMake adds the executable/library
# Do NOT remove the following variables. Modify the variables to suit your 
# project.

# Do NOT remove the following variables. Modify the variables to suit your project
set(USER_SOURCE_FILES
  src/main.cpp
  )

# Do not include individual assets here. Only add paths
set(USER_ASSETS_PATH
  ../../assets
  )

# Dependent project is compiled after dependency
set(USER_PROJECT_DEPENDENCIES
  "skopworksLib"
  )

# Libraries that the executable needs to link against
set(USER_EXECUTABLE_LINK_LIBRARIES
  "skopworksLib"
  )

# Tests require default compiler configurations. These can also be used for projects
# that require these options to be enabled.
load_default_configurations()
tloc_enable_exceptions()
tloc_enable_rtti()
tloc_enable_stl()

