#include "tlocPath.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

namespace tloc { namespace core { namespace io {

  Path::Path(const char* a_path) : m_path(a_path)
  {
    DoFixPath();
  }

  void Path::GetFileName(String& a_out) const
  {
    // Walk backwards and find the first backslash
    TLOC_UNUSED(a_out);
  }

  void Path::DoFixPath()
  {
    String oldPath(m_path);
    m_path.clear();

    replace_all(oldPath, '\\', '/');

    String match = "/";
    unique_copy_only_all(oldPath, m_path, match);
  }

};};};