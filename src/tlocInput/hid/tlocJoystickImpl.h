#ifndef _TLOC_JOYSTICK_IMPL_H_
#define _TLOC_JOYSTICK_IMPL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>
#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input { namespace hid {

  struct JoystickEvent
  {
  public:
    enum State
    {
      k_button0 = 0, k_button1, k_button2, k_button3, k_button4, k_button5,
      k_button6, k_button7, k_button8, k_button9, k_button10, k_button11,
      k_button12, k_button13, k_button14, k_button15, k_button16, k_button17,
      k_button18, k_button19, k_button20, k_button21, k_button22, k_button23,
      k_button24, k_button25, k_button26, k_button27, k_button28, k_button29,
      k_button30, k_button31, // 32 buttons as per dinput.h DIJOYSTATE struct

      k_count,
    }; typedef s32 state_code_type;

    struct xyAbs
    {
      Component::AxisAbs  m_x;
      Component::AxisAbs  m_y;
    };

    typedef JoystickEvent                                   this_type;
    typedef core_conts::Array<bool>                         button_cont;
    typedef core_conts::Array<Component::AxisAbs>           axis_cont;
    typedef core_conts::Array<xyAbs>                        slider_cont;
    typedef core_conts::Array<Component::Pov>               pov_cont;

  public:
    JoystickEvent()
    { Clear(); }

    JoystickEvent(const this_type& a_other)
      : m_buttons(a_other.m_buttons)
      , m_axes(a_other.m_axes)
      , m_pov(a_other.m_pov)
      , m_sliders(a_other.m_sliders)
    {
    }

    void Clear()
    {
      m_pov.clear();
      m_sliders.clear();

      m_pov.resize(4);
      m_sliders.resize(4);

      core::fill_all(m_buttons, false);

      for (axis_cont::iterator itr = m_axes.begin(), itrEnd = m_axes.end();
           itr != itrEnd; ++itr)
      {
        (*itr) = 0;
      }

      for (pov_cont::iterator itr = m_pov.begin(), itrEnd = m_pov.end();
           itr != itrEnd; ++itr)
      { itr->SetDirection(Component::Pov::k_centered); }

      for (slider_cont::iterator itr = m_sliders.begin(), itrEnd = m_sliders.end();
           itr != itrEnd; ++itr)
      {
        itr->m_x = 0;
        itr->m_y = 0;
      }
    }

    button_cont               m_buttons;
    axis_cont                 m_axes;
    pov_cont                  m_pov;
    slider_cont               m_sliders;

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
    typedef typename parent_type::joystick_event_type     joystick_event_type;

  public:
    JoystickImplBase(parent_type* a_parent, param_list_type a_params)
      : base_type(a_parent)
      , m_params(a_params)
    { }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    const param_list_type&
      GetParams() const
    { return m_params; }

    //! The minimal axis value
    static const int MIN_AXIS = -32768;

    //! The maximum axis value
    static const int MAX_AXIS = 32767;

  protected:
    using base_type::m_parent;

    joystick_event_type   m_currentState;
    param_list_type       m_params;
  };

};};};};

#endif