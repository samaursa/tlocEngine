#-----------------------------------------------------------
# - This project requires default compiler settings 

# Store the current settings
SET(CMAKE_CXX_FLAGS_OLD                 ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_OLD           ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE_OLD         ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_OLD  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

set(CMAKE_CXX_FLAGS                 ${CMAKE_CXX_FLAGS_DEFAULT})
set(CMAKE_CXX_FLAGS_DEBUG           ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT})
set(CMAKE_CXX_FLAGS_RELEASE         ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT})

# Generate tlocFilePaths.h file
FILE(WRITE ${CMAKE_SOURCE_DIR}/src/tlocVersion/tlocVersionFilePath.h "
#define VERSION_FILE_NAME \"${CMAKE_SOURCE_DIR}/src/tlocVersion.h\"
")

add_executable(
  tlocVersion 
  main.cpp
  tlocVersionFilePath.h
  )

# Run the generated executable after build
add_custom_target(tlocVersionTool ALL
  COMMAND ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tlocVersion
   DEPENDS tlocVersion
 )

#restore settings
set(CMAKE_CXX_FLAGS                 ${CMAKE_CXX_FLAGS_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_DEBUG           ${CMAKE_CXX_FLAGS_DEBUG_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_RELEASE         ${CMAKE_CXX_FLAGS_RELEASE_DEFAULT_OLD})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_DEFAULT_OLD})
