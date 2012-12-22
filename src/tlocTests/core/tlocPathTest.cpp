#include "tlocTestCommon.h"
#include <tlocCore/platform/tlocPlatform.h>

#if defined(TLOC_OS_IPHONE)
#import <Foundation/Foundation.h>
#endif

#include <stdio.h>
#include <cstring>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

#include <tlocCore/io/tlocPath.h>

namespace TestingIOPath
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
    strcpy(a_path, "/");
  }
#endif

  TEST_CASE("Core/io/Path", "")
  {
    {
      const char* path = "..//..\\/doc///users/\\//\\/myFile.txt";
      io::Path p(path);
      CHECK(StrCmp(p.GetPath(), "../../doc/users/myFile.txt") == 0);
    }

    {
      const char* path = "../../doc/users/myFile.txt";
      io::Path p(path);
      CHECK(StrCmp(p.GetPath(), path) == 0);

      String ret;
      p.GetFileName(ret);
      CHECK(ret.compare("myFile.txt") == 0);

      ret.clear();
      p.GetFileNameWithoutExtension(ret);
      CHECK(ret.compare("myFile") == 0);
      CHECK(ret.compare("myFile.txt") != 0);

      ret.clear();
      p.GetExtension(ret);
      CHECK(ret.compare("myFile.txt") != 0);
      CHECK(ret.compare("txt") == 0);

      ret.clear();
      p.GetPathWithoutFileName(ret);
      CHECK(ret.compare("../../doc/users") == 0);
    }
  }

  TEST_CASE("Core/io/Path/HasFileName", "")
  {
    io::Path p("../../someFolder/");
    CHECK(p.HasFilename() == false);
  }

  TEST_CASE("Core/io/Path/Exists", "")
  {
    char pathToCreateFiles[1024];
    GetPathToCreateFiles(pathToCreateFiles);

    {
      const char* fileName = "./testExists.txt";
      char path[1024];
      
      strcpy(path, pathToCreateFiles);
      strcat(path, fileName);

      FILE* f = fopen(path, "w");
      fclose(f);

      io::Path p(path);
      CHECK(p.FileExists());

      remove(path);
    }

    {
      const char* fileName = "./testExists.bin";
      char path[1024];

      strcpy(path, pathToCreateFiles);
      strcat(path, fileName);

      FILE* f = fopen(path, "wb");
      fclose(f);

      io::Path p(path);
      CHECK(p.FileExists());

      remove(path);
    }

    {
      io::Path p("./fileDoesNotExist.txt");
      CHECK_FALSE(p.FileExists());
    }

    {
      io::Path p("C:/ThisFolderShouldNotExist");
      CHECK_FALSE(p.FolderExists());
    }

    {
      io::Path p(pathToCreateFiles);
      CHECK(p.FolderExists());
    }
  }
};