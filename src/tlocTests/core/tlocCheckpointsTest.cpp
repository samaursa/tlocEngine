#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocCheckpoints.h>

namespace TestingCheckpoints
{
  using namespace tloc;
  using namespace core;

#define Check(a_cp, a_flag)\
  CHECK(a_cp[a_flag]);\
  CHECK(a_cp.IsMarked(a_flag))

#define CheckFalse(a_cp, a_flag)\
  CHECK_FALSE(a_cp[a_flag]);\
  CHECK_FALSE(a_cp.IsMarked(a_flag))

  TEST_CASE("core/utils/Checkpoints", "")
  {
    enum { k_flag1 = 0, k_flag2, k_flag3, k_flag4, k_count };

    core_utils::Checkpoints cp(k_count);

    cp.Mark(k_flag2);
    Check(cp, k_flag2);
    cp.Mark(k_flag2); // do it again to ensure same behavior
    Check(cp, k_flag2);

    cp.Unmark(k_flag2);
    CheckFalse(cp, k_flag2);
    cp.Unmark(k_flag2); // do it again to ensure same behavior
    CheckFalse(cp, k_flag2);

    CheckFalse(cp, k_flag4);
    cp.Toggle(k_flag4);
    Check(cp, k_flag4);
    cp.Toggle(k_flag4);
    CheckFalse(cp, k_flag4);

    for (tl_int i = 0; i < k_count; ++i)
    { CheckFalse(cp, i); }

    cp.Mark(k_flag1);
    Check(cp, k_flag1);

    cp.MarkAll();

    for (tl_int i = 0; i < k_count; ++i)
    { Check(cp, i); }

    cp.UnmarkAll();

    for (tl_int i = 0; i < k_count; ++i)
    { CheckFalse(cp, i); }

    cp.Mark(k_flag1);
    cp.Mark(k_flag3);
    cp.ToggleAll();
    CheckFalse(cp, k_flag1);
    CheckFalse(cp, k_flag3);
    Check(cp, k_flag2);
    Check(cp, k_flag4);

    cp.SetAllTo(true);
    for (tl_int i = 0; i < k_count; ++i)
    { Check(cp, i); }

    cp.SetAllTo(false);
    for (tl_int i = 0; i < k_count; ++i)
    { CheckFalse(cp, i); }

    CHECK_FALSE(cp.ReturnAndMark(k_flag1));
    CHECK(cp.ReturnAndMark(k_flag1));
    Check(cp, k_flag1);
    CHECK(cp.ReturnAndUnmark(k_flag1));
    CHECK_FALSE(cp.ReturnAndUnmark(k_flag1));

    CHECK_FALSE(cp.ReturnAndToggle(k_flag1));
    CHECK(cp.ReturnAndToggle(k_flag1));

    cp[k_flag1] = true;
    CHECK(cp[k_flag1]);
    CHECK(cp.IsMarked(k_flag1));
    CHECK_FALSE(cp.IsUnMarked(k_flag1));
    cp.Unmark(k_flag1);
    CHECK_FALSE(cp.IsMarked(k_flag1));
    CHECK(cp.IsUnMarked(k_flag1));

  }
};