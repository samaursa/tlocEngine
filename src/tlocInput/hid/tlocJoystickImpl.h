#ifndef _TLOC_JOYSTICK_IMPL_H_
#define _TLOC_JOYSTICK_IMPL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>
#include <tlocCore/data_structures/tlocTuple.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input { namespace hid {

  struct JoystickEvent
  {
  public:
    enum State
    {
      k_none = 0,

      k_xPos, k_yPos, k_zPos,

      k_xRot, k_yRot, k_zRot,

      k_slider0, k_slider1, // two sliders as per dinput.h DIJOYSTATE struct

      k_pov0, k_pov1, k_pov2, k_pov3, // 4 POVs as per dinput.h DIJOYSTATE struct

      k_button0, k_button1, k_button2, k_button3, k_button4, k_button5,
      k_button6, k_button7, k_button8, k_button9, k_button10, k_button11,
      k_button12, k_button13, k_button14, k_button15, k_button16, k_button17,
      k_button18, k_button19, k_button20, k_button21, k_button22, k_button23,
      k_button24, k_button25, k_button26, k_button27, k_button28, k_button29,
      k_button30, k_button31, // 32 buttons as per dinput.h DIJOYSTATE struct

      k_count,
    }; typedef s32 state_code_type;

    typedef core_ds::Tuple2s32            pos2_type;
    typedef core_ds::Tuple3s32            pos3_type;
    typedef core_ds::Tuple3s32            rot3_type;

  public:
    JoystickEvent()
      : m_posAxis(0)
      , m_rotAxis(0)
      , m_rglSlider(0)
      , m_povDirection(0)
      , m_stateCode(k_none)
    { }

    TLOC_DECL_AND_DEF_GETTER(pos3_type, GetPosAxis, m_posAxis);
    TLOC_DECL_AND_DEF_GETTER(rot3_type, GetRotAxis, m_rotAxis);
    TLOC_DECL_AND_DEF_GETTER(pos2_type, GetExtraAxis, m_rglSlider);
    TLOC_DECL_AND_DEF_GETTER(pos3_type, GetPovDirection, m_povDirection);
    TLOC_DECL_AND_DEF_GETTER(state_code_type, GetState, m_stateCode);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(pos3_type, SetPosAxis, m_posAxis);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(rot3_type, SetRotAxis, m_rotAxis);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(pos2_type, SetExtraAxis, m_rglSlider);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(pos3_type, SetPovDirection, m_povDirection);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(state_code_type, SetState, m_stateCode);

  private:
    pos3_type             m_posAxis;
    rot3_type             m_rotAxis;
    pos2_type             m_rglSlider;
    pos3_type             m_povDirection;
    state_code_type       m_stateCode;
  };

};};};

namespace tloc { namespace input { namespace hid { namespace priv {

  template <class T_ParentJoystick> class JoystickImpl_T;

  template <class T_ParentJoystick, class T_ParamList>
  class JoystickImplBase
    : public core_bclass::ImplBase<T_ParentJoystick>
  {
  public:
    typedef core_bclass::ImplBase<T_ParentJoystick>       base_type;
    typedef typename base_type::parent_type               parent_type;

    typedef T_ParamList                                   param_list_type;
    typedef typename parent_type::platform_type           platform_type;
    typedef typename parent_type::button_code_type        button_code_type;
    typedef typename parent_type::size_type               size_type;

  public:
    JoystickImplBase(parent_type* a_parent, param_list_type a_params)
      : base_type(a_parent)
      , m_params(a_params)
    { }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    const param_list_type&
      GetParams() const
    { return m_params; }

  protected:
    using base_type::m_parent;

    param_list_type   m_params;
  };

};};};};

#endif