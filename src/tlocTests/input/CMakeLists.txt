set(TLOC_TESTS_INPUT
  main.cpp
  tlocInputTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  )
#-------------------------------------------
# Project setup

add_executable(tlocTestsInput
  ${TLOC_TESTS_INPUT}
  )

add_dependencies(tlocTestsInput
  tlocCore
  tlocInput
  )

target_link_libraries(tlocTestsInput
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocCore.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocInput.lib
  )

# Find dinput.lib and add it as a link target
if(WIN32)
  if(${ARCH_DIR} MATCHES "x86")
    find_library(DIRECT_INPUT_LIB
      NAMES dinput8.lib
      PATHS ${TLOC_DEP_PATH}/src/WinSDK/Win32/lib
      )
  else()
    find_library(DIRECT_INPUT_LIB
      NAMES dinput8.lib
      PATHS ${TLOC_DEP_PATH}/src/WinSDK/x64/lib
      )
  endif()

  target_link_libraries(tlocTestsInput
    ${DIRECT_INPUT_LIB}
    )
endif()

# Filters to organize the source files
