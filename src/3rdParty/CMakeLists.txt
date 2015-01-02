add_library(3rdParty STATIC
  tloc3rdParty.h
  tloc3rdParty.cpp
  )

set_platform_specific_properties(3rdParty)

tloc_install_library(3rdParty "")
