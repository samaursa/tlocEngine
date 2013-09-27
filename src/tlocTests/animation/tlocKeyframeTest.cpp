#include "tlocTestCommon.h"

#include <tlocAnimation/types/tloc_types.h>

namespace TestingKeyframe
{
  using namespace tloc;
  using namespace tloc::anim_t;

  TEST_CASE("Animation/types/Keyframe", "")
  {
    keyframe_f32 kf;
    kf.SetValue(5.0f);
    kf.SetFrame(10);
    kf.SetInterpolationType(p_keyframe::k_ease_in_cubic);

    CHECK(kf.GetValue() == Approx(5.0f));
    CHECK(kf.GetFrame() == 10);
    CHECK( (kf.GetInterpolationType() == p_keyframe::k_ease_in_cubic) );
  }

  TEST_CASE("Animation/types/KeyframeSequence", "")
  {
    keyframe_sequence_f32 kfs;
    kfs.AddKeyframe(keyframe_f32(5.0f, 0));
    kfs.AddKeyframe(keyframe_f32(10.0f, 10));
    kfs.AddKeyframe(keyframe_f32(15.0f, 30));

    CHECK(kfs.size() == 3);

    CHECK(kfs.GetTotalFrames() == 30);
    CHECK(kfs.GetCurrentFrame() == 0);
    CHECK_FALSE(kfs.m_loop);

    CHECK(kfs.GetFramesBetween(0, 1) == 10);
    CHECK(kfs.GetFramesBetween(1, 2) == 20);
    CHECK(kfs.GetFramesBetweenCurrentPair() == 10);

    CHECK(kfs[0].GetFrame() == 0);
    CHECK(kfs[1].GetFrame() == 10);
    CHECK(kfs[2].GetFrame() == 30);

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);
    CHECK_FALSE(kfs.NextFrame());
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);

    for (tl_int i = 1; i < 10; ++i)
    { kfs.NextFrame(); }

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    for (tl_int i = 10; i < 30; ++i)
    { kfs.NextFrame(); }
    CHECK(kfs.GetCurrentFrame() == 30);

    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    kfs.SetCurrentFrame(5);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);

    kfs.SetCurrentFrame(11);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    kfs.SetCurrentFrame(25);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    kfs.SetCurrentFrame(30);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    kfs.Loop(true);
    CHECK(kfs.NextFrame());
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);

    CHECK(kfs.PrevFrame());
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    for (tl_int i = 0; i < 20; ++i)
    { kfs.PrevFrame(); }
    CHECK(kfs.GetCurrentFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 10);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 30);

    CHECK(kfs.PrevFrame());
    CHECK(kfs.GetKeyframePairAtCurrentFrame().first.GetFrame() == 0);
    CHECK(kfs.GetKeyframePairAtCurrentFrame().second.GetFrame() == 10);

    kfs.clear();

    CHECK(kfs.size() == 0);
  }
};