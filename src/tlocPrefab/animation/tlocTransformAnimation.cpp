#include "tlocTransformAnimation.h"

#include <tlocCore/tlocAssert.h>
#include <tlocAnimation/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace animation {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using anim_cs::transform_animation_sptr;

  typedef TransformAnimation::entity_type      entity_type;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::
    TransformAnimation(entity_mgr_ptr a_entMgr,
                       comp_pool_mgr_ptr a_poolMgr)
                      : base_type(a_entMgr, a_poolMgr)
                      , m_fps(24)
                      , m_startingFrame(0)
                      , m_paused(false)
                      , m_loop(false)
                      , m_reverse(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::component_ptr
    TransformAnimation::
    Construct(const kf_seq_type& a_keyframes, component_ptr a_existing) const
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    typedef ComponentPoolManager          pool_mgr;

    // Create the transform animation pool
    typedef anim_cs::transform_animation_pool             ta_pool;
    anim_cs::transform_animation_pool_vptr                taPool;

    anim_cs::transform_animation_sptr ta = a_existing;

    if (ta == nullptr)
    {
      taPool = m_compPoolMgr->GetOrCreatePool<anim_cs::TransformAnimation>();

      ta_pool::iterator itrTransformAnim = taPool->GetNext();
      (*itrTransformAnim)->SetValue(MakeShared<anim_cs::TransformAnimation>());

      ta = *(*itrTransformAnim)->GetValuePtr();
    }

    const TransformAnimation::size_type
      currSeqIndex = ta->GetCurrentKeyframeSequenceIndex();

    ta->AddKeyframeSet(a_keyframes);
    ta->SetCurrentKFSequence(ta->GetTotalKeyframeSequences() - 1);
    ta->SetFPS(m_fps);
    ta->SetFrame(m_startingFrame);
    ta->SetPaused(m_paused);
    ta->SetLooping(m_loop);
    ta->SetReverse(m_reverse);

    ta->SetCurrentKFSequence(currSeqIndex);

    return ta;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    Modify(component_ptr a_ta, 
           const kf_seq_type& a_keyframes, tl_size a_sequenceIndex) const
  {
    const TransformAnimation::size_type
      currSeqIndex = a_ta->GetCurrentKeyframeSequenceIndex();

    a_ta->ModifyKeyframeSet(a_keyframes, a_sequenceIndex);
    a_ta->SetCurrentKFSequence(a_sequenceIndex);
    a_ta->SetFPS(m_fps);
    a_ta->SetFrame(m_startingFrame);
    a_ta->SetPaused(m_paused);
    a_ta->SetLooping(m_loop);
    a_ta->SetReverse(m_reverse);

    a_ta->SetCurrentKFSequence(currSeqIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::this_type&
    TransformAnimation::
    Add(entity_ptr a_ent, const kf_seq_type& a_keyframes) const
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // TransformAnimation

    anim_cs::transform_animation_sptr ta = nullptr;

    if (a_ent->HasComponent<anim_cs::TransformAnimation>())
    {
      ta = a_ent->GetComponent<anim_cs::TransformAnimation>();
      Construct(a_keyframes, ta);
    }
    else
    {
      m_entMgr->InsertComponent(a_ent, Construct(a_keyframes, ta));
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    Modify(entity_ptr a_ent, const kf_seq_type& a_keyframes,
           tl_size a_sequenceIndex) const
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    TLOC_ASSERT(a_ent->HasComponent(transform_animation),
      "No TransformAnimation component to modify");

    anim_cs::transform_animation_sptr ta = 
      a_ent->GetComponent<TransformAnimation>();

    Modify(ta, a_keyframes, a_sequenceIndex);
  }

};};};