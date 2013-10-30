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
    typedef types::keyframe_sequence_mat4f32        kf_seq_type;

    struct KeyframeSequenceSetType
    {
    public:
      typedef KeyframeSequenceSetType               this_type;

    public:
      KeyframeSequenceSetType();
      KeyframeSequenceSetType(const KeyframeSequenceSetType& a_other);
      explicit KeyframeSequenceSetType(const kf_seq_type& a_kfSeq);

      kf_seq_type               m_kfSeq;
      tl_float                  m_frameDeltaT;
      f64                       m_startTime;
      f64                       m_totalTime;
      core_utils::Checkpoints   m_flags;
    };

  public:
    typedef TransformAnimation                                      this_type;
    typedef Component_T<this_type, components::transform_animation> base_type;
    typedef tl_size                                                 size_type;

    typedef core_conts::Array<KeyframeSequenceSetType>      cont_type;
    typedef cont_type::iterator                             iterator;

  public:
    TransformAnimation();

    void AddKeyframeSet(const kf_seq_type& a_keyframe);
    void ModifyKeyframeSet(const kf_seq_type& a_keyframe,
                           size_type a_index);
    void RemoveKeyframeSet(size_type a_index);

    kf_seq_type&         GetKeyframeSequence(size_type a_index);
    const kf_seq_type&   GetKeyframeSequence(size_type a_index) const;

    kf_seq_type&         GetCurrentKeyframeSequence();
    const kf_seq_type&   GetCurrentKeyframeSequence() const;

    void NextFrame();
    void PrevFrame();
    void SetFrame(size_type a_index);
    void GotoBegin();
    void GotoEnd();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetTotalKeyframeSequences, m_kfSeqSet.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentKeyframeSequenceIndex, m_currentSeq);
    TLOC_DECL_AND_DEF_GETTER(f64, GetStartTime, m_kfSeqSet[m_currentSeq].m_startTime);
    TLOC_DECL_AND_DEF_GETTER(f64, GetTotalTime, m_kfSeqSet[m_currentSeq].m_totalTime);
    TLOC_DECL_AND_DEF_GETTER
      (f64, GetFrameDeltaT, m_kfSeqSet[m_currentSeq].m_frameDeltaT);

    TLOC_DECL_GETTER(bool, IsLooping);
    TLOC_DECL_GETTER(bool, IsPaused);
    TLOC_DECL_GETTER(bool, IsStopped);
    TLOC_DECL_GETTER(bool, IsReversed);
    TLOC_DECL_GETTER(bool, IsKFSequenceChanged);
    TLOC_DECL_GETTER(size_type, GetFPS);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE
      (f64, SetStartTime, m_kfSeqSet[m_currentSeq].m_startTime);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE
      (f64, SetTotalTime, m_kfSeqSet[m_currentSeq].m_totalTime);

    TLOC_DECL_SETTER_BY_VALUE(bool, SetLooping);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetPaused);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetStopped);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetReverse);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetKFSequenceChanged);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetCurrentKFSequence);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetFPS);

  private:
    cont_type     m_kfSeqSet;
    size_type     m_currentSeq;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(TransformAnimation, transform_animation);
  TLOC_TYPEDEF_COMPONENT_POOL(transform_animation_sptr, transform_animation_sptr);

};};};

#endif