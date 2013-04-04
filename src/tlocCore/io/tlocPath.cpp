#include "tlocPath.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/io/tlocFileIO.h>

//------------------------------------------------------------------------
// Platform specific functionality

namespace tloc { namespace core { namespace io {

  using string::String;

  namespace
  {
    const char* g_pathSlash = "/";
    const char* g_extension = ".";
  };

  Path::Path(const char* a_path) : m_path(a_path)
  {
    TLOC_ASSERT(!m_path.empty(), "Path string is empty!");
    DoFixPath();
  }

  void Path::GetFileName(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }
  }

  void Path::GetFileNameWithoutExtension(String& a_out) const
  {
    GetFileName(a_out);
    tl_size pos = a_out.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = a_out.substr(0, pos); }
  }

  void Path::GetExtension(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }
  }

  void Path::GetPathWithoutFileName(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    a_out = m_path.substr(0, pos);
  }

  bool Path::FileExists() const
  {
    FileIO_ReadA fileChecker(m_path.c_str());
    if (fileChecker.Open() == tloc::common_error_types::error_success)
    { return true; }

    return false;
  }

  bool Path::FolderExists() const
  {
    String tempFileName = m_path + "/temp.temp";
    Path tempPath(tempFileName.c_str());

    FileIO_WriteA tempFile(tempPath.GetPath());
    if (tempFile.Open() == tloc::common_error_types::error_success)
    {
      tempFile.Close();
      if (tempFile.Delete() == tloc::common_error_types::error_failure)
      { /* LOG: Could not erase temporary file */ }

      return true;
    }

    return false;
  }

  bool Path::HasFilename() const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    pos = m_path.find(g_extension, pos);

    if (pos != String::npos)
    { return true; }

    return false;
  }

  void Path::SetPath(const char* a_path)
  {
    m_path = a_path;
    DoFixPath();
  }

  //------------------------------------------------------------------------
  // Helpers

  void Path::DoFixPath()
  {
    String oldPath(m_path);
    m_path.clear();

    replace_all(oldPath, '\\', '/');

    String match = "/";
    unique_copy_only_all(oldPath, m_path, match);
  }

};};};