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
                      , m_sequenceIndex(0)
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

    if (m_compPoolMgr->Exists(transform_animation) == false)
    { taPool = m_compPoolMgr->CreateNewPool<transform_animation_sptr>(); }
    else
    { taPool =  m_compPoolMgr->GetPool<transform_animation_sptr>(); }

    ta_pool::iterator itrTransformAnim = taPool->GetNext();
    itrTransformAnim->SetValue(transform_animation_sptr(new TransformAnimation()) );
    itrTransformAnim->GetValue()->AddKeyframeSet(a_keyframes);
    itrTransformAnim->GetValue()->SetFPS(m_fps);
    itrTransformAnim->GetValue()->SetFrame(m_startingFrame);
    itrTransformAnim->GetValue()->SetPaused(m_paused);
    itrTransformAnim->GetValue()->SetCurrentTransformSet(m_sequenceIndex);
    itrTransformAnim->GetValue()->SetLooping(m_loop);
    itrTransformAnim->GetValue()->SetReverse(m_reverse);

    m_entMgr->InsertComponent(a_ent, itrTransformAnim->GetValue().get());
  }

};};};