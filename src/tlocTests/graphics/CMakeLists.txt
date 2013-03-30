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

add_dependencies(tlocTestsGraphics
  tlocCore
  tlocGraphics
  tlocMath
  )

target_link_libraries(tlocTestsGraphics
  tlocCore
  tlocGraphics
  tlocMath
  )

if(MSVC)
target_link_libraries(tlocTestsGraphics
  glu32.lib
  OpenGL32.lib
  )
endif()

# Filters to organize the source files
