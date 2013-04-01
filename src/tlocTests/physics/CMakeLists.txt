set(TLOC_TESTS_PHYSICS
  main.cpp
  tlocPhysicsManagerTest.cpp
  tlocRigidBodySystemTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  )
#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocTestsPhysics)

include_directories(
  ${TLOC_DEP_PATH}/include/Box2D/
  )

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_BUNDLE_TYPE}
  ${TLOC_TESTS_PHYSICS}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  tlocPhysics
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  tlocMath
  tlocPhysics
  Box2D
  )

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
			MACOSX_BUNDLE_INFO_PLIST ${TLOC_PATH}/platform/iOS/tlocEngine.plist)
endif()

# Filters to organize the source files
