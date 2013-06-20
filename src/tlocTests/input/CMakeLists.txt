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

set(TLOC_CURRENT_EXEC_NAME tlocTestsInput)

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

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
      MACOSX_BUNDLE_INFO_PLIST ${TLOC_ENGINE_PATH}/platform/iOS/tlocEngine.plist)
endif()

# Find dinput.lib and add it as a link target
if(WIN32)
  if(${ARCH_DIR} MATCHES "x86")
    find_library(DIRECT_INPUT_LIB
      NAMES dinput8.lib
      PATHS ${TLOC_DEP_PATH}/src/WinSDK/WinSDK/Win32/lib
      )
  else()
    find_library(DIRECT_INPUT_LIB
      NAMES dinput8.lib
      PATHS ${TLOC_DEP_PATH}/src/WinSDK/WinSDK/x64/lib
      )
  endif()

  target_link_libraries(tlocTestsInput
    ${DIRECT_INPUT_LIB}
    )
endif()

# Filters to organize the source files
