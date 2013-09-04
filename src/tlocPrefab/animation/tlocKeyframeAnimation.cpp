#include "tlocKeyframeAnimation.h"

#include <tlocAnimation/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace animation {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using anim_cs::transform_animation_sptr;

  typedef KeyframeAnimation::entity_type      entity_type;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  KeyframeAnimation::
    KeyframeAnimation(core_cs::EntityManager* a_entMgr,
                      core_cs::ComponentPoolManager* a_poolMgr)
                      : Prefab_I(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    KeyframeAnimation::
    Add(entity_type* a_ent, const keyframe_set_type& a_keyframes)
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

    m_entMgr->InsertComponent(a_ent, itrTransformAnim->GetValue().get());
  }

};};};