set(TLOC_TESTS_CORE
  main.cpp
  tlocAlgorithmsTest.cpp
  tlocAnyTest.cpp
  tlocArrayFixedTest.cpp
  tlocArrayTest.cpp
  tlocBufferArgTest.cpp
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

add_executable(tlocTestsCore
  ${TLOC_TESTS_CORE}
  )

add_dependencies(tlocTestsCore
  tlocCore
  )

target_link_libraries(tlocTestsCore
  ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocCore.lib
  )

# Filters to organize the source files
