set(TLOC_TESTS_PHYSICS
  main.cpp
  tlocPhysicsManagerTest.cpp
  tlocRigidBodySystemTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  )
#-------------------------------------------
# Project setup

include_directories(
  ${TLOC_DEP_PATH}/include/Box2D/
  )

add_executable(tlocTestsPhysics
  ${TLOC_TESTS_PHYSICS}
  )

add_dependencies(tlocTestsPhysics
  tlocCore
  tlocMath
  tlocPhysics
  )

target_link_libraries(tlocTestsPhysics
  tlocCore
  tlocMath
  tlocPhysics
  Box2D
  )

# Filters to organize the source files
