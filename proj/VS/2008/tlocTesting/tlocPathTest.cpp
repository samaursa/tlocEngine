#include "tlocTestCommon.h"

#include <tlocCore/io/tlocPath.h>

#include <stdio.h>

namespace TestingIOPath
{
  using namespace tloc;
  using namespace tloc::core;

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
    {
      const char* fileName = "./testExists.txt";

      FILE* f = fopen(fileName, "w");
      fclose(f);

      io::Path p(fileName);
      CHECK(p.FileExists());

      remove(fileName);
    }

    {
      const char* fileName = "./testExists.bin";

      FILE* f = fopen(fileName, "wb");
      fclose(f);

      io::Path p(fileName);
      CHECK(p.FileExists());

      remove(fileName);
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
      io::Path p("../");
      CHECK(p.FolderExists());
    }
  }
};