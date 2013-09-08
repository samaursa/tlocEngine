#include "tlocTransformAnimationSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
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
    TransformAnimationSystem(event_manager_sptr a_eventMgr,
                             entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::transform_animation))
    , m_totalTime(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    InitializeEntity(const entity_manager*, const entity_type* a_ent)
  {
    const entity_type* ent = a_ent;

    const tl_size size =
      ent->GetComponents(anim_cs::TransformAnimation::k_component_type).size();

    for (tl_size i = 0; i < size; ++i)
    {
      anim_cs::TransformAnimation* texAnim =
        ent->GetComponent<anim_cs::TransformAnimation>(i);
      texAnim->SetStartTime(0);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TransformAnimationSystem::
    ShutdownEntity(const entity_manager*, const entity_type*)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimationSystem::
    Pre_ProcessActiveEntities(f64 a_deltaT)
  {
    m_totalTime += a_deltaT;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimationSystem::
    ProcessEntity(const entity_manager* , const entity_type* a_ent, f64 )
  {
    using namespace core::component_system;

    const entity_type* ent = a_ent;

    anim_cs::TransformAnimation* transAnim =
      ent->GetComponent<anim_cs::TransformAnimation>(0);

    f64 diff = m_totalTime - transAnim->GetStartTime();
    f64 fps = transAnim->GetFrameDeltaT();

    while (diff > fps)
    {
      if (transAnim->IsPaused() == false &&
        transAnim->IsStopped() == false)
      {
        transAnim->NextFrame();
      }

      transAnim->SetStartTime(transAnim->GetStartTime() + fps);
      diff = m_totalTime - transAnim->GetStartTime();
    }

    if (ent->HasComponent(components::transform_animation) &&
        transAnim->IsTransformSetChanged())
    {
      math_cs::Transform* transPtr =
        ent->GetComponent<math_cs::Transform>(0);

      typedef anim_cs::TransformAnimation::kf_seq_type    kf_seq;
      typedef kf_seq::keyframe_type                       kf_type;

      kf_seq& currKfSeq =
        transAnim->GetKeyframeSequence(transAnim->GetCurrentKFSequence());

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

      switch(kfPair.first.GetInterpolationType())
      {
      case kf_type::k_linear:
        {
          interpolatedVal = second * mu + first * (1.0f - mu);
          break;
        }
      case kf_type::k_ease_in_quadratic:
        {
          interpolatedVal = second * mu * mu + first * (1.0f - mu * mu);
          break;
        }
      case kf_type::k_ease_out_quadratic:
        {
          interpolatedVal = delta * -1.0f * mu * (mu - 2) + first;
          break;
        }
      case kf_type::k_ease_in_out_quadratic:
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
      case kf_type::k_ease_in_cubic:
        {
          interpolatedVal = delta * mu * mu * mu + first;
          break;
        }
      case kf_type::k_ease_out_cubic:
        {
          f32 mu2 = mu - 1;
          interpolatedVal = delta * (mu2 * mu2 * mu2 + 1) + first;
          break;
        }
      case kf_type::k_ease_in_out_cubic:
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
      case kf_type::k_ease_in_sin:
        {
          interpolatedVal =
            delta * -1.0f * Mathf32::Cos(mu * (Mathf32::PI * 0.5f)) +
            delta + first;
          break;
        }
      case kf_type::k_ease_out_sin:
        {
          interpolatedVal =
            delta * Mathf32::Sin(mu * (Mathf32::PI * 0.5f)) + first;
          break;
        }
      case kf_type::k_ease_in_out_sin:
        {
          interpolatedVal =
            delta * -0.5f * (Mathf32::Cos(Mathf32::PI * mu) - 1.0f) +
            first;
          break;
        }
      default:
        TLOC_ASSERT(false, "Unsupported interpolation type");
      }

      transPtr->SetTransformation(interpolatedVal);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void TransformAnimationSystem::
    Post_ProcessActiveEntities(f64)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  template class core_sptr::SharedPtr<TransformAnimationSystem>;

};};};