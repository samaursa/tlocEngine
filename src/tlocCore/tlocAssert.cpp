#include "tlocAssert.h"

namespace tloc { namespace core { namespace assert {

  bool AlwaysReturnFalse()
  { return false; }

  namespace {

    struct AssertBreakBase
    { virtual bool NoThrowBreak() const = 0; };

    struct AssertNoThrow
      : public AssertBreakBase
    {
      virtual bool NoThrowBreak() const
      { return true; }
    };

    struct AssertThrow
      : public AssertBreakBase
    {
      virtual bool NoThrowBreak() const
      { return false; }
    };

    AssertNoThrow g_noThrowBreak;
    AssertThrow   g_throwBreak;

    const AssertBreakBase* g_debugBreak = &g_noThrowBreak;

  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SetAssertThrow()
  { g_debugBreak = &g_throwBreak; }

  void
    SetAssertNoThrow()
  { g_debugBreak = &g_noThrowBreak; }

  bool
    NoThrowBreak()
  { return g_debugBreak->NoThrowBreak(); }

};};};