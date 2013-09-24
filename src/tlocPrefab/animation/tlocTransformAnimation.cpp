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
    TransformAnimation(core_cs::EntityManager* a_entMgr,
                      core_cs::ComponentPoolManager* a_poolMgr)
                      : Prefab_I(a_entMgr, a_poolMgr)
                      , m_fps(24)
                      , m_startingFrame(0)
                      , m_paused(false)
                      , m_loop(false)
                      , m_reverse(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    Add(entity_type* a_ent, const kf_seq_type& a_keyframes)
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    typedef ComponentPoolManager          pool_mgr;

    // Create the transform animation pool
    typedef anim_cs::transform_animation_sptr_pool        ta_pool;
    anim_cs::transform_animation_sptr_pool_sptr           taPool;

    anim_cs::TransformAnimation* ta = nullptr;

    if (a_ent->HasComponent(transform_animation))
    {
      ta = a_ent->GetComponent<TransformAnimation>();
    }
    else
    {
      if (m_compPoolMgr->Exists(transform_animation) == false)
      { taPool = m_compPoolMgr->CreateNewPool<transform_animation_sptr>(); }
      else
      { taPool =  m_compPoolMgr->GetPool<transform_animation_sptr>(); }

      ta_pool::iterator itrTransformAnim = taPool->GetNext();
      itrTransformAnim->SetValue(transform_animation_sptr(new TransformAnimation()) );

      m_entMgr->InsertComponent(a_ent, itrTransformAnim->GetValue().get());

      ta = itrTransformAnim->GetValue().get();
    }

    const TransformAnimation::size_type
      currSeqIndex = ta->GetCurrentKFSequence();

    ta->AddKeyframeSet(a_keyframes);
    ta->SetCurrentKFSequence(ta->GetNumSequences() - 1);
    ta->SetFPS(m_fps);
    ta->SetFrame(m_startingFrame);
    ta->SetPaused(m_paused);
    ta->SetLooping(m_loop);
    ta->SetReverse(m_reverse);

    ta->SetCurrentKFSequence(currSeqIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    Modify(entity_type* a_ent, const kf_seq_type& a_keyframes,
           tl_size a_sequenceIndex)
  {
    using namespace anim_cs::components;
    using anim_cs::TransformAnimation;

    TLOC_ASSERT(a_ent->HasComponent(transform_animation),
      "No TransformAnimation component to modify");

    anim_cs::TransformAnimation* ta = a_ent->GetComponent<TransformAnimation>();

    const TransformAnimation::size_type
      currSeqIndex = ta->GetCurrentKFSequence();

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