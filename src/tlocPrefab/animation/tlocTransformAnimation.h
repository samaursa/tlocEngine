#ifndef _TLOC_PREFAB_ANIMATION_KEYFRAME_H_
#define _TLOC_PREFAB_ANIMATION_KEYFRAME_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocAnimation/component_system/tlocTransformAnimation.h>

namespace tloc { namespace prefab { namespace animation {

  class TransformAnimation
    : public Prefab_TI<anim_cs::TransformAnimation>
  {
  public:
    typedef Prefab_TI<component_type>                         base_type;
    typedef TransformAnimation                                this_type;
    typedef tl_size                                           size_type;
    typedef anim_cs::TransformAnimation::kf_seq_type          kf_seq_type;

  public:
    TransformAnimation(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct(const kf_seq_type& a_keyframes, 
                            component_ptr a_existing = nullptr) const;
    void              Modify(component_ptr a_existing, 
                             const kf_seq_type& a_keyframes, 
                             tl_size a_sequenceIndex) const;

    entity_ptr        Create(const kf_seq_type& a_keyframes) const;
    const this_type&  Add(entity_ptr a_ent, const kf_seq_type& a_keyframes) const;
    void              Modify(entity_ptr a_ent, const kf_seq_type& a_keyframes,
                             tl_size a_sequenceIndex) const;

    TLOC_DECL_PARAM_VAR(tl_size, Fps, m_fps);
    TLOC_DECL_PARAM_VAR(size_type, StartingFrame, m_startingFrame);
    TLOC_DECL_PARAM_VAR(bool, Paused, m_paused);
    TLOC_DECL_PARAM_VAR(bool, Loop, m_loop);
    TLOC_DECL_PARAM_VAR(bool, Reverse, m_reverse);
  };

};};};

#endif