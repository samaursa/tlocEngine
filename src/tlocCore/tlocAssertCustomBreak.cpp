#include "tlocAssertCustomBreak.h"

namespace tloc { namespace core { namespace assert {

  namespace {

    // ///////////////////////////////////////////////////////////////////////
    // DefaultBreak

    class DefaultBreak
      : public CustomBreak
    {
    public:
      void Break() const
      { /* intentionally empty */ }
    };

    const DefaultBreak  g_defaultBreak;

    const CustomBreak*  g_currentBreak = &g_defaultBreak;

  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SetAssertCustomBreak(const CustomBreak* a_break)
  { g_currentBreak = a_break; }

  void
    SetAssertDefaultBreak()
  { g_currentBreak = &g_defaultBreak; }

  const CustomBreak*
    GetCustomBreak()
  { return g_currentBreak; }

  bool
    IsDefaultBreak()
  { return g_currentBreak == &g_defaultBreak; }

};};};