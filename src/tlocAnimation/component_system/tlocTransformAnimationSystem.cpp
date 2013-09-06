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

      kf_seq& currKfSeq =
        transAnim->GetKeyframeSequence(transAnim->GetCurrentKFSequence());

      const kf_seq::size_type currFrame = currKfSeq.GetCurrentFrame();
      const kf_seq::size_type totalFrames = currKfSeq.GetTotalFrames();

      kf_seq::kf_pair kfPair = currKfSeq.GetKeyframePairAtCurrentFrame();

      const kf_seq::size_type currRelativeFrame = currFrame - kfPair.first.GetFrame();

      // interpolate between the two keyframes (linear for now - this needs
      // to change to accommodate for all different types of interpolations)

      const f32 mu = totalFrames == 0 ? 0 : (f32)currRelativeFrame / (f32)totalFrames;

      kf_seq::keyframe_type::value_type
        interpolatedVal = kfPair.second.GetValue() * mu +
                          kfPair.first.GetValue() * (1.0f - mu);

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