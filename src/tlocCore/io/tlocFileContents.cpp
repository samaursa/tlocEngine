#include "tlocFileContents.h"

namespace tloc { namespace core { namespace io {

  // ///////////////////////////////////////////////////////////////////////
  // FileContents

  FileContents::
    FileContents()
    : m_path("INVALID PATH")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FileContents::
    FileContents(const path_type& a_path, const string_type& a_string)
    : m_path(a_path)
    , m_fileContents(a_string)
  { }

};};};