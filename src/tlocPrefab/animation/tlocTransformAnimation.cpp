#include "tlocTransformAnimation.h"

#include <tlocAnimation/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace animation {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using anim_cs::transform_animation_sptr;

  typedef TransformAnimation::entity_type      entity_type;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::
    TransformAnimation(entity_mgr_ptr a_entMgr,
                       comp_pool_mgr_ptr a_poolMgr)
                      : Prefab_I(a_entMgr, a_poolMgr)
                      , m_fps(24)
                      , m_startingFrame(0)
                      , m_paused(false)
                      , m_loop(false)
                      , m_reverse(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::this_type&
    TransformAnimation::
    Add(entity_ptr a_ent, const kf_seq_type& a_keyframes)
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    typedef ComponentPoolManager          pool_mgr;

    // Create the transform animation pool
    typedef anim_cs::transform_animation_pool             ta_pool;
    anim_cs::transform_animation_pool_vptr                taPool;

    anim_cs::transform_animation_vptr ta = nullptr;

    if (a_ent->HasComponent(transform_animation))
    {
      ta = a_ent->GetComponent<TransformAnimation>();
    }
    else
    {
      if (m_compPoolMgr->Exists(transform_animation) == false)
      { taPool = m_compPoolMgr->CreateNewPool<anim_cs::TransformAnimation>(); }
      else
      { taPool =  m_compPoolMgr->GetPool<anim_cs::TransformAnimation>(); }

      ta_pool::iterator itrTransformAnim = taPool->GetNext();
      (*itrTransformAnim)->SetValue(anim_cs::TransformAnimation());

      m_entMgr->InsertComponent(a_ent, (*itrTransformAnim)->GetValue());

      ta = (*itrTransformAnim)->GetValue();
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

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    Modify(entity_ptr a_ent, const kf_seq_type& a_keyframes,
           tl_size a_sequenceIndex)
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    TLOC_ASSERT(a_ent->HasComponent(transform_animation),
      "No TransformAnimation component to modify");

    anim_cs::transform_animation_vptr ta = a_ent->GetComponent<TransformAnimation>();

    const TransformAnimation::size_type
      currSeqIndex = ta->GetCurrentKeyframeSequenceIndex();

    ta->ModifyKeyframeSet(a_keyframes, a_sequenceIndex);
    ta->SetCurrentKFSequence(a_sequenceIndex);
    ta->SetFPS(m_fps);
    ta->SetFrame(m_startingFrame);
    ta->SetPaused(m_paused);
    ta->SetLooping(m_loop);
    ta->SetReverse(m_reverse);

    ta->SetCurrentKFSequence(currSeqIndex);
  }

};};};