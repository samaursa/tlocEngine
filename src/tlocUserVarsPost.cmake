#------------------------------------------------------------------------------
# This file is included AFTER CMake adds the executable/library. Any operations
# you want to perform that are done after the project has been created, can
# be performed in this file.

# Add the version tool - currently DISABLED for APPLE due to iOS builds
if(NOT TLOC_PLATFORM_IOS AND NOT DISTRIBUTION_BUILD)
  # Make tlocVersion and tlocVersionTool as dependencies for all projects
  foreach(lib ${SOLUTION_LIBRARY_PROJECTS})
    add_dependencies(${lib}
      tlocVersion
      tlocVersionTool
      )
  endforeach()

  # Make tlocVersion and tlocVersionTool as dependencies for all projects
  foreach(lib ${SOLUTION_EXECUTABlE_PROJECTS})
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
