#ifndef _TLOC_ANIMATION_COMPONENT_SYSTEM_TRANSFORM_ANIMATION_H_
#define _TLOC_ANIMATION_COMPONENT_SYSTEM_TRANSFORM_ANIMATION_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocAnimation/types/tlocKeyframe.h>
#include <tlocAnimation/component_system/tlocComponentType.h>

namespace tloc { namespace animation { namespace component_system {

  class TransformAnimation
    : public core_cs::Component_T<TransformAnimation, components::transform_animation>
  {
  public:
    typedef types::keyframe_set_mat4f32                    keyframe_set_type;

    struct KeyframeSetInfo
    {
    public:
      typedef KeyframeSetInfo       this_type;

    public:
      KeyframeSetInfo();
      KeyframeSetInfo(const KeyframeSetInfo& a_other);
      explicit KeyframeSetInfo(const keyframe_set_type& a_keyframes);

      keyframe_set_type         m_keyframes;
      tl_float                  m_frameDeltaT;
      f64                       m_startTime;
      core_utils::Checkpoints   m_flags;
    };

  public:
    typedef TransformAnimation                                      this_type;
    typedef Component_T<this_type, components::transform_animation> base_type;
    typedef tl_size                                                 size_type;

    typedef core_conts::Array<KeyframeSetInfo>      cont_type;
    typedef cont_type::iterator                     iterator;

  public:
    TransformAnimation();

    void AddKeyframeSet(const keyframe_set_type& a_keyframe);
    void ModifyKeyframeSet(const keyframe_set_type& a_keyframe,
                           size_type a_index);
    void RemoveKeyframeSet(size_type a_index);

    keyframe_set_type&         GetKeyframeSet(size_type a_index);
    const keyframe_set_type&   GetKeyframeSet(size_type a_index) const;

    void NextFrame();
    void PrevFrame();
    void SetFrame(size_type a_index);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumKeyframeSets, m_keyframeSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentKeyframeSetIndex, m_currentSet);
    TLOC_DECL_AND_DEF_GETTER(f64, GetStartTime, m_keyframeSets[m_currentSet].m_startTime);
    TLOC_DECL_AND_DEF_GETTER
      (f64, GetFrameDeltaT, m_keyframeSets[m_currentSet].m_frameDeltaT);

    TLOC_DECL_GETTER(bool, IsLooping);
    TLOC_DECL_GETTER(bool, IsPaused);
    TLOC_DECL_GETTER(bool, IsStopped);
    TLOC_DECL_GETTER(bool, IsTransformSetChanged);
    TLOC_DECL_GETTER(size_type, GetFPS);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE
      (f64, SetStartTime, m_keyframeSets[m_currentSet].m_startTime);

    TLOC_DECL_SETTER_BY_VALUE(bool, SetLooping);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetPaused);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetStopped);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetTransformSetChanged);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetCurrentTransformSet);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetFPS);

  private:
    cont_type     m_keyframeSets;
    size_type     m_currentSet;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(TransformAnimation, transform_animation);
  TLOC_TYPEDEF_COMPONENT_POOL(transform_animation_sptr, transform_animation_sptr);

};};};

#endif