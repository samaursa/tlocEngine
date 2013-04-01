set(TLOC_TESTS_CORE
  main.cpp
  tlocAlgorithmsTest.cpp
  tlocAnyTest.cpp
  tlocArrayFixedTest.cpp
  tlocArrayTest.cpp
  tlocBufferArgTest.cpp
  tlocComponentPoolManagerTest.cpp
  tlocContainerTraitsTest.cpp
  tlocEntityManagerTest.cpp
  tlocEntityTest.cpp
  tlocEventManagerTest.cpp
  tlocFileIOTest.cpp
  tlocForwardListTest.cpp
  tlocGroupIDTest.cpp
  tlocHashMapTest.cpp
  tlocHashtableTest.cpp
  tlocIteratorTest.cpp
  tlocListTest.cpp
  tlocMemoryPoolTest.cpp
  tlocMemoryTest.cpp
  tlocObjectCounterTest.cpp
  tlocPair.cpp
  tlocPathTest.cpp
  tlocProtectedBufferTest.cpp
  tlocQueueTest.cpp
  tlocRandomTest.cpp
  tlocRangeTest.cpp
  tlocSharedPtrTest.cpp
  tlocStackTest.cpp
  tlocStringTest.cpp
  tlocStrongTypeTest.cpp
  tlocTableTest.cpp
  tlocTemplateDispatchTest.cpp
  tlocTestCommon.cpp
  tlocTestCommon.h
  tlocTimeTest.cpp
  tlocTupleTest.cpp
  tlocTypesTest.cpp
  tlocTypesUtilsTests.cpp
  tlocTypeTraitsTest.cpp
  tlocUniquePtrTest.cpp
  tlocUtilsTest.cpp
  tlocVariadicTest.cpp
  )
#-------------------------------------------
# Project setup

set(TLOC_CURRENT_EXEC_NAME tlocTestsCore)

add_executable(${TLOC_CURRENT_EXEC_NAME}
  ${TLOC_BUNDLE_TYPE}
  ${TLOC_TESTS_CORE}
  )

add_dependencies(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  )

target_link_libraries(${TLOC_CURRENT_EXEC_NAME}
  tlocCore
  )

if(APPLE)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     ${TLOC_CURRENT_EXEC_NAME})
    set_target_properties(${TLOC_CURRENT_EXEC_NAME} PROPERTIES 
			MACOSX_BUNDLE_INFO_PLIST ${TLOC_PATH}/platform/iOS/tlocEngine.plist)
endif()

# Filters to organize the source files
