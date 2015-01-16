set(TLOC_TESTS_INPUT
  main.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  )

if(WIN32)
  set(TLOC_TESTS_INPUT
    ${TLOC_TESTS_INPUT}
    tlocInputTest.cpp
    )
endif()

#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocInputTests)

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_APP_TYPE}
  ${TLOC_TESTS_INPUT}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocInput
  tlocMath
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocInput
  tlocMath
  )

if(MSVC)
  target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
    dinput8.lib
    )
endif()

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
      MACOSX_BUNDLE_INFO_PLIST ${SOLUTION_INSTALL_PATH}/platform/iOS/tlocEngine.plist)
endif()

set_platform_specific_properties(${TLOC_CURRENT_EXEC_NAME})

# Filters to organize the source files
