#------------------------------------------------------------------------------
# In most cases, this file should NOT be modified by the user. User modifiable
# files are tlocUserVarsPre.cmake and tlocUserVarsPost.cmake

#------------------------------------------------------------------------------
include(tlocUserVarsPre.cmake)

#------------------------------------------------------------------------------
set(SOURCE_FILES
  ${USER_SOURCE_FILES}
  ../tlocVersionCheck.cpp
  )

#------------------------------------------------------------------------------
set(ASSETS_PATH
  ${USER_ASSETS_PATH}
  )

#------------------------------------------------------------------------------
# Create the project
if (${USER_CURRENT_PROJECT_TYPE} STREQUAL ${USER_PROJECT_TYPE_EXE})

  add_executable(${USER_CURRENT_PROJECT_NAME}
    ${TLOC_APP_TYPE}
    ${SOURCE_FILES}
    ${ASSETS_PATH}
    )
  add_common_libraries(${USER_CURRENT_PROJECT_NAME})
  if (ASSETS_PATH)
    add_apple_plist(${USER_CURRENT_PROJECT_NAME} ${ASSETS_PATH})
  else()
    add_apple_plist(${USER_CURRENT_PROJECT_NAME} "")
  endif()

  # Link the user defined libraries with this project
  if(USER_EXECUTABLE_LINK_LIBRARIES)
    target_link_libraries(${USER_CURRENT_PROJECT_NAME}
      ${USER_EXECUTABLE_LINK_LIBRARIES}
      )
  endif()

elseif(${USER_CURRENT_PROJECT_NAME} STREQUAL ${USER_PROJECT_TYPE_LIB})

  add_library(${USER_CURRENT_PROJECT_NAME} STATIC
    ${SOURCE_FILES}
    )

endif()

# Add dependencies (if any)
if(USER_PROJECT_DEPENDENCIES)
  add_dependencies(${USER_CURRENT_PROJECT_NAME}
    ${USER_PROJECT_DEPENDENCIES}
    )
endif()

#------------------------------------------------------------------------------
include(tlocUserVarsPost.cmake)
