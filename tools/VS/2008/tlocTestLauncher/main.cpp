#include <tlocCore/tlocBase.h>
#include <tlocCore/memory/tlocLinkMe.cpp>

#include <iostream>
#include <vector>
using namespace std;

#include "ProcessLauncher.h"
#include "dirent.h"

#include <tlocCore/io/tlocPath.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct filePaths
{
  typedef vector<tloc::core::io::Path>  cont_type;
  cont_type m_files;
};

void PopulatePaths(filePaths& a_paths, const char* a_currPath)
{
  DIR *dir;
  struct dirent *ent;
  tloc::core::String currPath = a_currPath;

  dir = opendir(a_currPath);

  if (dir != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      switch(ent->d_type)
      {
      case DT_REG:
        {
          a_paths.m_files.push_back( (currPath + ent->d_name).c_str() );
          break;
        }
      case DT_DIR:
        {
          if (tloc::core::StrCmp(ent->d_name, ".") == 0 ||
              tloc::core::StrCmp(ent->d_name, "..") == 0)
          { break; }

          tloc::core::String newPath = a_currPath;
          newPath += ent->d_name;
          newPath += "/";
          PopulatePaths(a_paths, newPath.c_str());
          break;
        }
      default:
        {}
      }
    }
  }
}

int main()
{
  filePaths p;

  const size_t envBuffSize = 2048;
  char buff[envBuffSize];
  //LPTSTR buff = new TCHAR[envBuffSize];

  if (GetEnvironmentVariableA("TLOC_PATH", buff, 1000) ==
      ERROR_ENVVAR_NOT_FOUND)
  {
    cout << "Unable to find TLOC_PATH env variable. Quitting.\n";
    return -1;
  }

  tloc::core::io::Path t( (tloc::core::String(buff) + "/bin/tests/").c_str() );

  PopulatePaths(p, + (tloc::core::String(t.GetPath()) + "/").c_str() );

  filePaths::cont_type::iterator itr = p.m_files.begin();
  filePaths::cont_type::iterator itrEnd = p.m_files.end();

  for (; itr != itrEnd; ++itr)
  {
    cout << itr->GetPath() << endl;
  }

  //DIR *dir;
  //struct dirent *ent;

  //dir = opendir("./");
  //if (dir != NULL)
  //{
  //  while ((ent = readdir(dir)) != NULL)
  //  {
  //    switch(ent->d_type)
  //    {
  //    case DT_REG:
  //      {
  //        cout << ent->d_name << endl;
  //        break;
  //      }
  //    case DT_DIR:
  //      {
  //        cout << ent->d_name << "/\n";
  //        break;
  //      }
  //    default:
  //      {
  //        cout << ent->d_name << "*\n";
  //      }
  //    }
  //  }

  //  closedir(dir);
  //}
}