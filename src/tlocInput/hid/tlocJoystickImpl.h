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
    enum ButtonCode
    {
      none = 0,
      button1,
      button2,
      button3,
      button4,
      button5,
      button6,
      button7,
      button8,
      button9,
      button10,
    }; typedef s32 button_code_type;

    typedef core_ds::Tuple2s32            pos2_type;
    typedef core_ds::Tuple3s32            pos3_type;
    typedef core_ds::Tuple3s32            rot3_type;

  public:


  private:
    pos3_type             m_posAxis;
    rot3_type             m_rotAxis;
    pos2_type             m_rglSlider;
    pos3_type             m_povDirection;
    button_code_type      m_buttonCode;

  };

};};};

namespace tloc { namespace input { namespace hid { namespace priv {

  template <class T_ParentJoystick> class JoystickImpl;

  template <class T_ParentJoystick, class T_ParamList>
  class JoystickImplBase
    : public core_bclass::ImplBase<T_ParentJoystick>
  {
  public:
    typedef core_bclass::ImplBase<T_ParentJoystick>       base_type;
    typedef typename base_type::parent_type               parent_type;

    typedef T_ParamList                                   param_list_type;
    typedef typename parent_type::platform_type           platform_type;

  public:

  protected:
  };

};};};};

#endif