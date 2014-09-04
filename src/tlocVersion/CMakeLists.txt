#-----------------------------------------------------------
# - This project requires default compiler settings 

# Store the current settings
set(CMAKE_CXX_FLAGS_OLD                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_OLD           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_OLD         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_OLD  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

set(CMAKE_CXX_FLAGS                 ${CMAKE_CXX_FLAGS_DEFAULT})
set(CMAKE_CXX_FLAGS_DEBUG           ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT})
set(CMAKE_CXX_FLAGS_RELEASE         ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT})

if(TLOC_COMPILER_MSVC)
  # VS2010 gives warnings if these options are in the command line
  string(REGEX REPLACE "/Zm1000"  "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REGEX REPLACE "/GX"      "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()


# Generate tlocFilePaths.h file
FILE(WRITE ${CMAKE_SOURCE_DIR}/src/tlocVersion/tlocVersionFilePath.h "
#define VERSION_FILE_NAME \"${CMAKE_SOURCE_DIR}/INSTALL/tlocVersion.h\"
")

add_executable(
  tlocVersion 
  main.cpp
  tlocVersionFilePath.h
  )

# Run the generated executable after build
add_custom_target(tlocVersionTool ALL
  COMMAND ${TLOC_ENGINE_INSTALL_PATH}/bin/${CMAKE_CFG_INTDIR}/tlocVersion 
  DEPENDS tlocVersion
 )

if(TLOC_COMPILER_MSVC)
  set_target_properties(tlocVersion
    PROPERTIES
    LINK_FLAGS_RELEASE "/LTCG"
    LINK_FLAGS_RELWITHDEBINFO "/LTCG"
    )
endif()
