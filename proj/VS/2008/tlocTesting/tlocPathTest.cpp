#include "tlocTestCommon.h"

#include <tlocCore/io/tlocPath.h>

namespace TestingIOPath
{
  using namespace tloc;
  using namespace tloc::core;

  TEST_CASE("Core/io/Path", "")
  {
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

    {
      const char* path = "..//..\\/doc///users/\\//\\/myFile.txt";
      io::Path p(path);
      CHECK(StrCmp(p.GetPath(), "../../doc/users/myFile.txt") == 0);
    }
  }
};