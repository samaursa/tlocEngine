set(TLOC_TESTS_MATH
  main.cpp
  tlocAngleTest.cpp
  tlocCircleTest.cpp
  tlocContiguityTest.cpp
  tlocMathTest.cpp
  tlocMatrix2Test.cpp
  tlocMatrix3Test.cpp
  tlocMatrix4Test.cpp
  tlocMatrixTest.cpp
  tlocPythagorasTest.cpp
  tlocRectangleTest.cpp
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

add_executable(tlocTestsMath
  ${TLOC_TESTS_MATH}
  )

target_link_libraries(tlocTestsMath
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocCore.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocMath.lib
  )

# Filters to organize the source files
