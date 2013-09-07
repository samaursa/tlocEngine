#ifndef _TLOC_PREFAB_ANIMATION_KEYFRAME_H_
#define _TLOC_PREFAB_ANIMATION_KEYFRAME_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocAnimation/component_system/tlocTransformAnimation.h>

namespace tloc { namespace prefab { namespace animation {

  class TransformAnimation
    : public Prefab_I
  {
  public:
    typedef TransformAnimation                                this_type;
    typedef tl_size                                           size_type;
    typedef anim_cs::TransformAnimation::kf_seq_type          kf_seq_type;

  public:
    TransformAnimation(core_cs::EntityManager* a_entMgr,
             core_cs::ComponentPoolManager* a_poolMgr);

    void          Add(entity_type* a_ent, const kf_seq_type& a_keyframes);

    TLOC_DECL_PARAM_VAR(tl_size, Fps, m_fps);
    TLOC_DECL_PARAM_VAR(size_type, StartingFrame, m_startingFrame);
    TLOC_DECL_PARAM_VAR(bool, Paused, m_paused);
    TLOC_DECL_PARAM_VAR(tl_size, Sequence, m_sequenceIndex);
    TLOC_DECL_PARAM_VAR(bool, Loop, m_loop);
  };

};};};

#endif