set(TLOC_TESTS_PREFAB
  main.cpp
  tlocTestCommon.h
  tlocTestCommon.cpp
  tlocArcBallTest.cpp
  tlocArcBallControlTest.cpp
  tlocCameraTest.cpp
  tlocCuboidTest.cpp
  tlocDynamicTextTest.cpp
  tlocFanTest.cpp
  tlocMaterialTest.cpp
  tlocMeshTest.cpp
  tlocQuadTest.cpp
  tlocRigidBodyTest.cpp
  tlocSceneNodeTest.cpp
  tlocSpriteTest.cpp
  tlocTextureCoordsTest.cpp
  tlocTransformAnimationTest.cpp
  tlocTransformTest.cpp
  )

set(TLOC_TESTS_PREFAB_ASSETS
  ${TLOC_ENGINE_PATH}/assets
  )

#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocTestsPrefab)

link_directories(
  ${TLOC_DEP_INSTALL_PATH}/lib/
  )

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_APP_TYPE}
  ${TLOC_TESTS_PREFAB}
  ${TLOC_TESTS_PREFAB_ASSETS}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  tlocGraphics
  tlocAnimation
  tlocPhysics
  tlocPrefab
  tlocInput
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  tlocGraphics
  tlocAnimation
  tlocPrefab
  tlocPhysics
  tlocInput
  FreeType
  Box2D
  )

if(MSVC)
target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  glu32.lib
  OpenGL32.lib
  dinput8.lib
  )
endif()

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
      MACOSX_BUNDLE_INFO_PLIST ${TLOC_ENGINE_PATH}/platform/iOS/tlocEngine.plist)
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES
      RESOURCE "${TLOC_TESTS_PREFAB_ASSETS}")
endif()

set_platform_specific_properties(${TLOC_CURRENT_EXEC_NAME})

# Filters to organize the source files
