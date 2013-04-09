#-----------------------------------------------------------
# - This project require some settings to be turned on

set(CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT})
set(CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT})

if(TLOC_COMPILER_MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG           "/DTLOC_DEBUG /Od /Gm  /EHsc /RTC1 /MTd /GR /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELEASE         "/DTLOC_RELEASE /O2 /Ob2 /Oi /Ot /GL /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/DTLOC_RELEASE_DEBUGINFO /O2 /Ob2 /Oi /Ot /Gm /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP")
elseif(TLOC_COMPILER_XCODE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTLOC_DEBUG -fno-rtti -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DTLOC_RELEASE -fno-rtti -Wno-unused-function")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DTLOC_RELEASE_DEBUGINFO -fno-rtti -Wno-unused-function")
else()
  message("Configuration not applied because compiler is unsupported (or not detected properly)")
endif()

set(tlocAllTests
  tlocTestsCore
  tlocTestsGraphics
  tlocTestsInput
  tlocTestsMath
  tlocTestsPhysics
  )

add_definitions(
  -DTLOC_ENABLE_CPPUNWIND 
  -DTLOC_ENABLE_CPPRTTI 
  -DTLOC_USING_STL 
  )

include_directories(
  ${TLOC_DEP_PATH}/include/CATCH/
  )

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(physics)

if(TLOC_COMPILER_MSVC)
  foreach(testProj ${tlocAllTests})
    if(TARGET ${testProj})
      set_target_properties(${testProj}
        PROPERTIES
        FOLDER tlocTests
        )
    else()
      message("Test project ${testProj} not generated successfully.")
    endif()
  endforeach()
endif()
