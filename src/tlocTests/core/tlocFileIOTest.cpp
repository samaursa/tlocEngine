#include "tlocTestCommon.h"

#include <stdio.h>

#include <tlocCore/io/tlocFileIO.h>

namespace TestingFileIO
{
  using namespace tloc;
  using namespace tloc::core;

  TEST_CASE("Core/io/FileIO", "Testing file input output")
  {
    const char* sentence = "This is a test sentence.";
    const char* fileName = "TestingFileIO.txt";

    FILE* m_file = fopen("TestingFileIO.txt", "w");
    REQUIRE(m_file != NULL);

    fputs(sentence, m_file);
    fclose(m_file);

    io::FileIO_ReadA fileReader(fileName);
    CHECK(fileReader.Open() == common_error_types::error_success);

    String fileContents;
    fileReader.GetContents(fileContents);

    CHECK(fileContents.compare(sentence) == 0);
    CHECK(fileReader.Close() == common_error_types::error_success );

    CHECK(fileReader.Delete() == common_error_types::error_success );
  }
};