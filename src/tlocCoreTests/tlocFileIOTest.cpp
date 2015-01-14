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
  using string::String;

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

    // Prepare the file that we will be testing
    FILE* m_file = fopen(path, "w");
    REQUIRE((m_file != nullptr));

    fputs(sentence, m_file);
    fclose(m_file);

    // Start our tests
    io::FileIO_ReadA fileReader = io::FileIO_ReadA(core_io::Path(path));
    CHECK_FALSE(fileReader.IsOpen());
    CHECK(fileReader.Open() == common_error_types::error_success);
    CHECK(fileReader.IsOpen());

    String fileContents;
    fileReader.GetContents(fileContents);
    CHECK(fileContents.compare(sentence) == 0);

    core_io::FileContents fc;
    fileReader.GetContents(fc);
    CHECK(fc.GetContents().compare(sentence) == 0);
    CHECK(fc.GetPath() == fileReader.GetPath());

    // should close the file fileReader currently has and copy the rhs file
    // reader into fileReader
    fileReader = io::FileIO_ReadA(core_io::Path(path));
    CHECK_FALSE(fileReader.IsOpen());
    CHECK(fileReader.Open() == common_error_types::error_success);
    CHECK(fileReader.IsOpen());

    CHECK(fileReader.Close() == common_error_types::error_success );
    CHECK_FALSE(fileReader.IsOpen());

    // write something to the file
    const char* appendedWords = " Appended words.";

    io::FileIO_AppendA fileAppend( (core_io::Path(path)) );

    {
      TLOC_TEST_ASSERT
      { fileAppend.Write(appendedWords); }
      TLOC_TEST_ASSERT_CHECK();

      REQUIRE(fileAppend.Open() == ErrorSuccess);
      REQUIRE(fileAppend.Write(appendedWords) == ErrorSuccess);
      REQUIRE(fileAppend.Close() == ErrorSuccess);

      REQUIRE(fileReader.Open() == ErrorSuccess);
      String appendedFileContents;
      fileReader.GetContents(appendedFileContents);
      CHECK(appendedFileContents.compare(String(sentence) + appendedWords) == 0);
      REQUIRE(fileReader.Close() == ErrorSuccess);

      TLOC_TEST_ASSERT
      { fileAppend.Write(appendedWords); }
      TLOC_TEST_ASSERT_CHECK();

      {
        core_io::FileContents fileContents;
        using namespace core_io::f_file_io;
        CHECK(OpenAndGetContents<core_io::p_file_io::Ascii>
              (core_io::Path(path), fileContents) == ErrorSuccess);
      }

      CHECK(fileReader.Delete() == common_error_types::error_success);
    }

    {
      // write something to the file that has new lines
      const char* twoLines = "Two\nLines.";

      REQUIRE(fileAppend.Open() == ErrorSuccess);
      REQUIRE(fileAppend.Write(twoLines, 
                               core_str::StrLen(twoLines)) == ErrorSuccess);
      REQUIRE(fileAppend.Close() == ErrorSuccess);

      REQUIRE(fileReader.Open() == ErrorSuccess);
      String appendedFileContents;
      fileReader.GetContents(appendedFileContents);
      CHECK(appendedFileContents.compare(twoLines) == 0);
      REQUIRE(fileReader.Close() == ErrorSuccess);

      CHECK(fileReader.Delete() == common_error_types::error_success);
    }

    io::FileIO_ReadA fileReaderNoFile(core_io::Path("fileDoesNotExist.txt"));
    CHECK(fileReaderNoFile.Open() != ErrorSuccess);
  }
};
