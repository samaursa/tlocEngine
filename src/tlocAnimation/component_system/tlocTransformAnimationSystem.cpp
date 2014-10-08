#include "tlocTransformAnimationSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocAnimation/component_system/tlocTransformAnimation.h>

#include <stdio.h>

namespace tloc { namespace animation { namespace component_system {

  using namespace core_ds;

  typedef TransformAnimationSystem::error_type        error_type;

  // ///////////////////////////////////////////////////////////////////////
  // TransformAnimationSystem

  TransformAnimationSystem::
    TransformAnimationSystem(event_manager_ptr a_eventMgr,
                             entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::transform_animation))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    const tl_size size =
      a_ent->GetComponents(anim_cs::TransformAnimation::k_component_type).size();

    for (tl_size i = 0; i < size; ++i)
    {
      transform_animation_sptr texAnim =
        a_ent->GetComponent<anim_cs::TransformAnimation>(i);
      texAnim->SetStartTime(0);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimationSystem::
    Pre_ProcessActiveEntities(f64 )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimationSystem::
    ProcessEntity(entity_ptr a_ent, f64 a_deltaT)
  {
    using namespace core::component_system;

    transform_animation_sptr transAnim =
      a_ent->GetComponent<anim_cs::TransformAnimation>(0);

    transAnim->SetTotalTime(transAnim->GetTotalTime() + a_deltaT);

    f64 diff = transAnim->GetTotalTime() - transAnim->GetStartTime();
    f64 fps = transAnim->GetFrameDeltaT();

    while (diff > fps)
    {
      if (transAnim->IsPaused() == false &&
        transAnim->IsStopped() == false)
      {
        transAnim->NextFrame();
      }

      transAnim->SetStartTime(transAnim->GetStartTime() + fps);
      diff = transAnim->GetTotalTime() - transAnim->GetStartTime();
    }

    if (a_ent->HasComponent(components::transform_animation) &&
        transAnim->IsKFSequenceChanged())
    {
      math_cs::transform_sptr transPtr =
        a_ent->GetComponent<math_cs::Transform>(0);

      typedef anim_cs::TransformAnimation::kf_seq_type    kf_seq;
      typedef kf_seq::keyframe_type                       kf_type;

      kf_seq& currKfSeq = transAnim->GetCurrentKeyframeSequence();

      if (currKfSeq.size() == 0)
      { return; }

      const kf_seq::size_type currFrame = currKfSeq.GetCurrentFrame();
      const kf_seq::size_type totalFrames = currKfSeq.GetFramesBetweenCurrentPair();

      kf_seq::kf_pair kfPair = currKfSeq.GetKeyframePairAtCurrentFrame();

      const kf_seq::size_type currRelativeFrame = currFrame - kfPair.first.GetFrame();

      // interpolate between the two keyframes (linear for now - this needs
      // to change to accommodate for all different types of interpolations)

      const f32 mu = totalFrames == 0 ? 0 : (f32)currRelativeFrame / (f32)totalFrames;

      kf_seq::keyframe_type::value_type interpolatedVal;

      const kf_type::value_type& first = kfPair.first.GetValue();
      const kf_type::value_type& second = kfPair.second.GetValue();
      const kf_type::value_type& delta = (second - first);

      using namespace anim_t::p_keyframe;

      switch(kfPair.first.GetInterpolationType())
      {
      case k_linear:
        {
          interpolatedVal = second * mu + first * (1.0f - mu);
          break;
        }
      case k_ease_in_quadratic:
        {
          interpolatedVal = second * mu * mu + first * (1.0f - mu * mu);
          break;
        }
      case k_ease_out_quadratic:
        {
          interpolatedVal = delta * -1.0f * mu * (mu - 2) + first;
          break;
        }
      case k_ease_in_out_quadratic:
        {
          f32 mu2 = mu * 2;
          if (mu2 < 1)
          {
            interpolatedVal = delta * 0.5f * mu2 * mu2 + first;
          }
          else
          {
            mu2--;
            interpolatedVal =
              (first - second) * 0.5f * (mu2 * (mu2 - 2) - 1) + first;
          }
          break;
        }
      case k_ease_in_cubic:
        {
          interpolatedVal = delta * mu * mu * mu + first;
          break;
        }
      case k_ease_out_cubic:
        {
          f32 mu2 = mu - 1;
          interpolatedVal = delta * (mu2 * mu2 * mu2 + 1) + first;
          break;
        }
      case k_ease_in_out_cubic:
        {
          f32 mu2 = mu * 2;
          if (mu2 < 1)
          {
            interpolatedVal = delta * 0.5f * mu2 * mu2 * mu2 + first;
          }
          else
          {
            mu2 -= 2;
            interpolatedVal = delta * 0.5f * (mu2 * mu2 * mu2 + 2) + first;
          }
          break;
        }
      case k_ease_in_sin:
        {
          interpolatedVal =
            delta * -1.0f * math::Cos(math_t::MakeRadian(mu * (Mathf32::PI * 0.5f))) +
            delta + first;
          break;
        }
      case k_ease_out_sin:
        {
          interpolatedVal =
            delta * math::Sin(math_t::MakeRadian(mu * (Mathf32::PI * 0.5f))) + first;
          break;
        }
      case k_ease_in_out_sin:
        {
          interpolatedVal =
            delta * -0.5f * (math::Cos(math_t::MakeRadian(Mathf32::PI * mu)) - 1.0f) +
            first;
          break;
        }
      default:
        TLOC_ASSERT_FALSE("Unsupported interpolation type");
      }

      transPtr->SetTransformation(interpolatedVal);
      transPtr->SetUpdateRequired(false);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void TransformAnimationSystem::
    Post_ProcessActiveEntities(f64)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::anim_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TransformAnimationSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(TransformAnimationSystem);