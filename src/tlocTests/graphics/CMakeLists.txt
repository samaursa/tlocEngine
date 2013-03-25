set(TLOC_TESTS_GRAPHICS
  main.cpp
  tlocAttributeVariableTest.cpp
  tlocColorTest.cpp
  tlocComponentPoolManagerTest.cpp
  tlocFOVTest.cpp
  tlocFrustumTest.cpp
  tlocGLGeneralTest.cpp
  tlocGLObjectTest.cpp
  tlocGraphicsModesTest.cpp
  tlocImageLoaderTest.cpp
  tlocQuadTest.cpp
  tlocShaderComponentTest.cpp
  tlocShaderOperatorTest.cpp
  tlocShaderProgramTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  tlocUniformVariableTest.cpp
  tlocVertexTest.cpp
  tlocWindowTest.cpp
  )
#-------------------------------------------
# Project setup

add_executable(tlocTestsGraphics
  ${TLOC_TESTS_GRAPHICS}
  )

target_link_libraries(tlocTestsGraphics
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocCore.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocGraphics.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocMath.lib
  )

if(MSVC)
target_link_libraries(tlocTestsGraphics
  glu32.lib
  OpenGL32.lib
  )
endif()

# Filters to organize the source files
