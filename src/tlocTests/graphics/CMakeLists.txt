set(TLOC_TESTS_GRAPHICS
  main.cpp
  tlocTestCommon.h
  tlocAttributeVariableTest.cpp
  tlocColorTest.cpp
  tlocGLGeneralTest.cpp
  tlocGLObjectTest.cpp
  tlocGraphicsModesTest.cpp
  tlocImageTest.cpp
  tlocImageLoaderTest.cpp
  tlocQuadTest.cpp
  tlocObjLoaderTest.cpp
  tlocShaderComponentTest.cpp
  tlocShaderOperatorTest.cpp
  tlocShaderProgramTest.cpp
  tlocSpriteTest.cpp
  tlocSpriteLoaderTest.cpp
  tlocTestCommon.cpp
  tlocTextureCoordsTest.cpp
  tlocUniformVariableTest.cpp
  tlocVertexTest.cpp
  tlocWindowTest.cpp
  )

set(TLOC_TESTS_GRAPHICS_ASSETS
  ${TLOC_ENGINE_PATH}/assets
  )

#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocTestsGraphics)

include_directories(
  ${TLOC_DEP_PATH}/include/FreeType/
  )

link_directories(
  ${TLOC_DEP_BUILD_PATH}/src/FreeType/
  )

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_APP_TYPE}
  ${TLOC_TESTS_GRAPHICS}
  ${TLOC_TESTS_GRAPHICS_ASSETS}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocGraphics
  tlocMath
  tlocInput
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocGraphics
  tlocMath
  tlocInput
  )

if(MSVC)
target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  glu32.lib
  OpenGL32.lib
  freetype.lib
  )
endif()

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
  set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
    MACOSX_BUNDLE_INFO_PLIST ${TLOC_ENGINE_PATH}/platform/iOS/tlocEngine.plist)
  set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES
                        RESOURCE "${TLOC_TESTS_GRAPHICS_ASSETS}")
endif()

set_platform_specific_properties(${TLOC_CURRENT_EXEC_NAME})

# Filters to organize the source files
#source_group(assets FILES ${TLOC_TESTS_GRAPHICS_ASSETS})
