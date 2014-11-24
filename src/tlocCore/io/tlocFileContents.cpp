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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FileContents::
    FileContents(this_type&& a_temp)
    : m_path(a_temp.m_path)
    , m_fileContents(a_temp.m_fileContents)
  { }

};};};