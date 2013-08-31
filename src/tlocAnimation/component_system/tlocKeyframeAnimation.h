#ifndef _TLOC_ANIMATION_COMPONENT_SYSTEM_KEYFRAME_ANIMATION_H_
#define _TLOC_ANIMATION_COMPONENT_SYSTEM_KEYFRAME_ANIMATION_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocAnimation/types/tlocKeyframe.h>
#include <tlocAnimation/component_system/tlocComponentType.h>

namespace tloc { namespace animation { namespace component_system {

  class KeyframeAnimation
    : public core_cs::Component_T<KeyframeAnimation, keyframe_animation>
  {
  public:
    typedef KeyframeAnimation                                       this_type;
    typedef Component_T<this_type, components::keyframe_animation>  base_type;
    typedef tl_size                                                 size_type;

    typedef Keyframe_T                                keyframe_type;
    typedef core_conts::Array<keyframe_type>        cont_type;
    typedef cont_type::iterator                     iterator;

  public:
    KeyframeAnimation();

    void AddKeyframe(const keyframe_type& a_keyframe);
    void ModifyKeyframe(const keyframe_type& a_keyframe,
                        size_type a_index);
    void RemoveKeyframe(size_type a_index);

    keyframe_type&         GetKeyframeSet(size_type a_index);
    const keyframe_type&   GetKeyframeSet(size_type a_index) const;

    void NextFrame();
    void PrevFrame();
    void SetFrame(size_type a_index);


  private:

  };

};};};

#endif