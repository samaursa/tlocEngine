#-----------------------------------------------------------
# - This project require some settings to be turned on

# set normal (non-strict) compiler flags
tloc_add_definitions()

# add all the test projects
set(tlocAllTests
  tlocTestsCore
  tlocTestsGraphics
  tlocTestsInput
  tlocTestsMath
  tlocTestsPhysics
  tlocTestsAnimation
  tlocTestsPrefab
  )

include_directories(
  ${TLOC_DEP_INSTALL_PATH}
  ${TLOC_DEP_INSTALL_PATH}/include/CATCH/
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  )

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(animation)
add_subdirectory(prefab)

if(TLOC_COMPILER_MSVC)
  foreach(testProj ${tlocAllTests})
    if(TARGET ${testProj})
      # MSVC requires LTCG for Release
      set_target_properties(${testProj}
        PROPERTIES
        LINK_FLAGS_RELEASE "/LTCG"
        LINK_FLAGS_RELWITHDEBINFO "/LTCG"
        )
      set_target_properties(${testProj}
        PROPERTIES
        FOLDER tlocTests
        )
      if(NOT DISTRIBUTION_BUILD)
        # Make tlocVersion and tlocVersionTool as dependencies for all projects
        add_dependencies(${testProj}
          tlocVersion
          tlocVersionTool
          )
      endif()
    else()
      message("Test project ${testProj} not generated successfully.")
    endif()
  endforeach()
endif()
