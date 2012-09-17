#include "tlocPath.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

namespace tloc { namespace core { namespace io {

  namespace
  {
    const char* g_pathSlash = "/";
    const char* g_extension = ".";
  };

  Path::Path(const char* a_path) : m_path(a_path)
  {
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

  void Path::GetAbsolutePath(String& a_out) const
  {
    TLOC_UNUSED(a_out);
  }

  bool Path::Exists() const
  {
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