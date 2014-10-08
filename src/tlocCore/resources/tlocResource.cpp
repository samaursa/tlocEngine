#include "tlocResource.h"

namespace tloc { namespace core { namespace resources {

  // ///////////////////////////////////////////////////////////////////////
  // Resource_I

  template <typename T>
  Resource_I::
    Resource_I(path_type a_path)
    : m_ucid(core::UCID<T>().GetClassID())
    , m_path(a_path)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Resource_I::
    ~Resource_I()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Resource_I::
    operator==(const this_type& a_other) const
  {
    return m_ucid == a_other.m_ucid &&
           m_path == a_other.m_path;
  }

};};};