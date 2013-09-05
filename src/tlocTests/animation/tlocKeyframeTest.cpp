#include "tlocTestCommon.h"

#include <tlocAnimation/types/tloc_types.h>

namespace TestingKeyframe
{
  using namespace tloc;
  using namespace tloc::anim_t;

  TEST_CASE("Animation/types/KeyframeSequence", "")
  {
    keyframe_sequence_f32 kfs;
    kfs.AddKeyframe(keyframe_f32(5.0f, 0));
    kfs.AddKeyframe(keyframe_f32(10.0f, 10));
    kfs.AddKeyframe(keyframe_f32(15.0f, 20));

    CHECK(kfs.size() == 3);

    CHECK(kfs.GetTotalFrames() == 20);
    CHECK(kfs.GetCurrentFrame() == 0);
    CHECK(kfs.m_loop == false);
    CHECK(kfs.m_stopOnLastFrame == true);

    CHECK(kfs[0].GetFrame() == 0);
    CHECK(kfs[1].GetFrame() == 10);
    CHECK(kfs[2].GetFrame() == 20);

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);
    kfs.NextFrame();
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);

    for (tl_int i = 1; i < 10; ++i)
    { kfs.NextFrame(); }

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 20);

    for (tl_int i = 10; i < 20; ++i)
    { kfs.NextFrame(); }
    CHECK(kfs.GetCurrentFrame() == 20);

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 20);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 20);

    kfs.clear();

    CHECK(kfs.size() == 0);
  }
};