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

  path::
    path(const buffer_arg& a_path) : m_path(a_path)
  {
    TLOC_LOG_CORE_WARN_IF(m_path.empty()) << "Path is empty";
    do_fix_path();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_file_name(String& a_out) const -> const this_type&
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_file_name_without_extension(String& a_out) const -> const this_type&
  {
    get_file_name(a_out);
    tl_size pos = a_out.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = a_out.substr(0, pos); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_extension(String& a_out) const -> const this_type&
  {
    tl_size pos = m_path.find_last_of(g_extension);
    if (pos != String::npos)
    { a_out = m_path.substr(pos + 1); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_path_without_file_name(String& a_out) const -> const this_type&
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    a_out = m_path.substr(0, pos);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_file_name() const -> string_type
  {
    string_type toRet;
    get_file_name(toRet);
    return toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_file_name_without_extension() const -> string_type
  {
    string_type toRet;
    get_file_name_without_extension(toRet);
    return toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_extension() const -> string_type
  {
    string_type toRet;
    get_extension(toRet);
    return toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    get_path_without_file_name() const -> string_type
  {
    string_type toRet;
    get_path_without_file_name(toRet);
    return toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    path::
    file_exists() const
  {
    FileIO_ReadA fileChecker = FileIO_ReadA(core_io::path(m_path));
    if (fileChecker.open() == tloc::common_error_types::error_success)
    { return true; }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    path::
    folder_exists() const
  {
    String tempFileName = m_path + "/temp.temp";
    path tempPath(tempFileName);

    FileIO_WriteA tempFile(tempPath);
    if (tempFile.open() == tloc::common_error_types::error_success)
    {
      tempFile.close();
      if (tempFile.delete() == tloc::common_error_types::error_failure)
      {
        TLOC_LOG_CORE_WARN() << "Could not erase temporary file: " << tempFileName;
      }

      return true;
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    path::
    has_file_name() const
  {
    tl_size pos = m_path.find_last_of(g_pathSlash);
    pos = m_path.find(g_extension, pos);

    if (pos != String::npos)
    { return true; }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    path::
    set_path(const buffer_arg& a_path) -> this_type&
  {
    m_path = a_path;
    do_fix_path();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    path::
    operator==(const this_type& a_other) const
  { return m_path == a_other.m_path; }

  //------------------------------------------------------------------------
  // Helpers

  void
    path::
    do_fix_path()
  {
    String oldPath(m_path);
    m_path.clear();

    replace_all(oldPath, '\\', '/');

    String match = "/";
    unique_copy_only_all(oldPath, m_path, match);
  }

};};};