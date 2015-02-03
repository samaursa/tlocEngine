#include "tlocUserData.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // UserData

  UserData::
    UserData()
    : base_type("UserData")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  UserData::
    UserData(const any_type& a_other)
    : base_type("UserData")
    , m_data(a_other)
  { }

};};};