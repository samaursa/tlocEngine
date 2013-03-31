#-----------------------------------------------------------
# - This project require some settings to be turned on

# Store the current settings
SET(CMAKE_CXX_FLAGS_OLD                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_OLD           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_OLD         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_OLD  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

#if(MSVC)
#  set(CMAKE_CXX_FLAGS_DEBUG           "/Od /Gm  /EHsc /RTC1 /MTd /GR /W4 /WX /c /Zi /TP")
#  set(CMAKE_CXX_FLAGS_RELEASE         "/O2 /Ob2 /Oi /Ot /GL /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP")
#  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/O2 /Ob2 /Oi /Ot /Gm /EHsc /MT /Gy /GR /W4 /WX /c /Zi /TP")
#endif()

set(CMAKE_CXX_FLAGS "-x objective-c++")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT})

#SET(CMAKE_CXX_FLAGS_DEFAULT                 ${CMAKE_CXX_FLAGS})
#set(CMAKE_CXX_FLAGS_DEBUG_DEFAULT           ${CMAKE_CXX_FLAGS_DEBUG})
#set(CMAKE_CXX_FLAGS_RELEASE_DEFAULT         ${CMAKE_CXX_FLAGS_RELEASE})
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})


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

link_directories(${TLOC_DEP_PATH}/lib/${ARCH_DIR}/) 

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(physics)

if(MSVC)
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

#restore settings
set(CMAKE_CXX_FLAGS                 ${CMAKE_CXX_FLAGS_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_DEBUG           ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_RELEASE         ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT_OLD})
