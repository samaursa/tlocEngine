#include "tlocCallbackReturn.h"

namespace tloc { namespace core { namespace dispatch {

  // ///////////////////////////////////////////////////////////////////////
  // CallbackReturn

  CallbackReturn::
    CallbackReturn()
    : m_veto(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  CallbackReturn::this_type&
    CallbackReturn::
    Veto()
  { m_veto = true; return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  CallbackReturn::this_type&
    CallbackReturn::
    Continue()
  { m_veto = false; return *this; }

};};};