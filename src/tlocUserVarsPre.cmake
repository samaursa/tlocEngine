# -----------------------------------------------------------------------------
# Add include and link directories
# -----------------------------------------------------------------------------

include(${SOLUTION_PATH}/INSTALL/tlocLibraries.cmake)

# common includes
include_directories(
  ${TLOC_DEP_INCLUDE_DIRECTORIES}
  ${SOLUTION_PATH}/INSTALL/
  ${SOLUTION_PATH}/src/
  )

# for tests
link_directories(
  ${TLOC_LINK_DIRECTORIES}
  )

# Add the version tool - currently DISABLED for APPLE due to iOS builds
if(NOT TLOC_PLATFORM_IOS AND NOT DISTRIBUTION_BUILD)
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

# assets file name change
set(ASSETS_PATH_FILE_NAME "tlocAssetsPath")
