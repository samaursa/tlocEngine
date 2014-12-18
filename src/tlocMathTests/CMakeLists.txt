set(TLOC_TESTS_MATH
  main.cpp
  tlocAngleTest.cpp
  tlocCircleTest.cpp
  tlocContiguityTest.cpp
  tlocCuboidTest.cpp
  tlocFOVTest.cpp
  tlocFrustumTest.cpp
  tlocMathTest.cpp
  tlocMatrix2Test.cpp
  tlocMatrix3Test.cpp
  tlocMatrix4Test.cpp
  tlocMatrixTest.cpp
  tlocPythagorasTest.cpp
  tlocRangeTest.cpp
  tlocRayTest.cpp
  tlocRectangleTest.cpp
  tlocScaleTest.cpp
  tlocStatFunctionTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  tlocTransformTest.cpp
  tlocVector2Test.cpp
  tlocVector3Test.cpp
  tlocVector4Test.cpp
  tlocVectorTest.cpp
  )
#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocMathTests)

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_APP_TYPE}
  ${TLOC_TESTS_MATH}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  )

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
      MACOSX_BUNDLE_INFO_PLIST ${TLOC_ENGINE_PATH}/platform/iOS/tlocEngine.plist)
endif()

set_platform_specific_properties(${TLOC_CURRENT_EXEC_NAME})

# Filters to organize the source files
