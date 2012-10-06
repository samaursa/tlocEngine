#include "tlocTestCommon.h"
#include <tlocCore/platform/tlocPlatform.h>

#if defined(TlOC_OS_IPHONE)
#import <Foundation/Foundation.h>
#endif

#include <stdio.h>
#include <cstring>

#include <tlocCore/io/tlocFileIO.h>

namespace TestingFileIO
{
  using namespace tloc;
  using namespace tloc::core;

  void GetPathToCreateFiles(char* a_path);

#if defined(TLOC_OS_IPHONE)
  void GetPathToCreateFiles(char* a_path)
  {
    const char* path = [NSTemporaryDirectory() cStringUsingEncoding:[NSString defaultCStringEncoding]];
    strcpy(a_path, path);
  }
#else
  void GetPathToCreateFiles(char* a_path)
  {
    a_path[0] = '\0';
  }
#endif

  TEST_CASE("Core/io/FileIO", "Testing file input output")
  {
    const char* sentence = "This is a test sentence.";
    const char* fileName = "TestingFileIO.txt";
    char path[1024];

    GetPathToCreateFiles(path);
    strcat(path, fileName);

    FILE* m_file = fopen(path, "w");
    REQUIRE(m_file != NULL);

    fputs(sentence, m_file);
    fclose(m_file);

    io::FileIO_ReadA fileReader(path);
    CHECK(fileReader.Open() == common_error_types::error_success);

    String fileContents;
    fileReader.GetContents(fileContents);

    CHECK(fileContents.compare(sentence) == 0);
    CHECK(fileReader.Close() == common_error_types::error_success );

    CHECK(fileReader.Delete() == common_error_types::error_success );
  }
};
