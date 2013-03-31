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

if(APPLE)
  set(TLOC_BUNDLE_TYPE MACOSX_BUNDLE)
else()
  set(TLOC_BUNDLE_TYPE "")
endif()

add_executable(tlocTestsCore
  ${TLOC_BUNDLE_TYPE}
  ${TLOC_TESTS_CORE}
  )

add_dependencies(tlocTestsCore
  tlocCore
  )

target_link_libraries(tlocTestsCore 
  tlocCore
  )

if(APPLE)
  #set(EXECUTABLE_NAME tlocTestsCore)
  #set(PRODUCT_NAME    tlocTestsCore)
  set(EXECUTABLE_NAME "\${EXECUTABLE_NAME}")
  set(PRODUCT_NAME    "\${PRODUCT_NAME}")
  set(BUNDLE_NAME     tlocTestsCore)
  set_target_properties(tlocTestsCore PROPERTIES 
			MACOSX_BUNDLE_INFO_PLIST ${TLOC_PATH}/platform/iOS/tlocEngine.plist)
endif()

# Filters to organize the source files
