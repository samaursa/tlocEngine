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
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocCore.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocMath.lib
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocPhysics.lib
  ${TLOC_DEP_PATH}/lib/${ARCH_DIR}/${CMAKE_CFG_INTDIR}/Box2D.lib
  )

# Filters to organize the source files
