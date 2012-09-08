#include "tlocTestCommon.h"

#include <stdio.h>

#include <tlocCore/io/tlocFileIO.h>

namespace TestingFileIO
{
  using namespace tloc::core;

  TEST_CASE("Core/io/FileIO", "Testing file input output")
  {
    const char* sentence = "This is a test sentence.";
    const char* fileName = "TestingFileIO.txt";

    FILE* m_file = fopen("TestingFileIO.txt", "a");
    REQUIRE(m_file != NULL);

    fputs(sentence, m_file);
    fclose(m_file);

    io::FileIO_ReadA fileReader(fileName);
    fileReader.Open();

    String fileContents;
    fileReader.GetContents(fileContents);

    CHECK(fileContents.compare(sentence) == 0);
    CHECK(fileReader.Close() == (error::common_error_types::error_success) );

    remove(fileName);
  }
};