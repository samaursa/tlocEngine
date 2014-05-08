#include "tlocPath.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/io/tlocFileIO.h>

#include <tlocCore/logging/tlocLogger.h>

//------------------------------------------------------------------------
// Platform specific functionality

namespace tloc { namespace core { namespace io {

  using string::String;

  namespace
  {
    const char* g_pathSlash = "/";
    const char* g_extension = ".";
  };

  // ///////////////////////////////////////////////////////////////////////
  // Path

  Path::
    Path(const BufferArg& a_path) : m_path(a_path)
  {
    TLOC_LOG_CORE_WARN_IF(m_path.empty()) << "Path is empty";
    DoFixPath();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Path::
    GetFileName(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Path::
    GetFileNameWithoutExtension(String& a_out) const
  {
    GetFileName(a_out);
    tl_size pos = a_out.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = a_out.substr(0, pos); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Path::
    GetExtension(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Path::
    GetPathWithoutFileName(String& a_out) const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    a_out = m_path.substr(0, pos);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Path::
    FileExists() const
  {
    FileIO_ReadA fileChecker = FileIO_ReadA(core_io::Path(m_path));
    if (fileChecker.Open() == tloc::common_error_types::error_success)
    { return true; }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Path::
    FolderExists() const
  {
    String tempFileName = m_path + "/temp.temp";
    Path tempPath(tempFileName);

    FileIO_WriteA tempFile(tempPath);
    if (tempFile.Open() == tloc::common_error_types::error_success)
    {
      tempFile.Close();
      if (tempFile.Delete() == tloc::common_error_types::error_failure)
      {
        TLOC_LOG_CORE_WARN() << "Could not erase temporary file: " << tempFileName;
      }

      return true;
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Path::
    HasFilename() const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    pos = m_path.find(g_extension, pos);

    if (pos != String::npos)
    { return true; }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Path::
    SetPath(const BufferArg& a_path)
  {
    m_path = a_path;
    DoFixPath();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Path::
    operator==(const this_type& a_other) const
  { return m_path == a_other.m_path; }

  //------------------------------------------------------------------------
  // Helpers

  void
    Path::
    DoFixPath()
  {
    String oldPath(m_path);
    m_path.clear();

    replace_all(oldPath, '\\', '/');

    String match = "/";
    unique_copy_only_all(oldPath, m_path, match);
  }

};};};