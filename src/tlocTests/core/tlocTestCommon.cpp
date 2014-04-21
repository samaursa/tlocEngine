#include "tlocTestCommon.h"

namespace tloc { namespace tests {

  namespace {
    const ThrowOnBreak g_throwOnBreak;
  }

  // ///////////////////////////////////////////////////////////////////////
  // ThrowOnBreak

  void
    ThrowOnBreak::
    Break() const
  {
    throw exception::Assert();
  }

  // -----------------------------------------------------------------------

  const core::assert::CustomBreak*
    GetThrowOnBreak()
  {
    return &g_throwOnBreak;
  }

};};