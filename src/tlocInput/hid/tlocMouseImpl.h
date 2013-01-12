#ifndef TLOC_MOUSE_IMPL_H
#define TLOC_MOUSE_IMPL_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input {

  ///-------------------------------------------------------------------------
  /// A mouse event that is sent as the argument when a mouse event
  /// is fired.
  ///-------------------------------------------------------------------------
  struct MouseEvent
  {
    enum ButtonCode
    {
      none    = 0,
      left    = 1 << 0,
      right   = 1 << 1,
      middle  = 1 << 2,
      button4 = 1 << 3,
      button5 = 1 << 4,
      button6 = 1 << 5,
      button7 = 1 << 6,
      button8 = 1 << 7,

      count = core::utils::EnumCounter<button8, true>::result,
    };  typedef u32 button_code_type;

    MouseEvent(ButtonCode a_code = none) : m_buttonCode(a_code) {}

    button_code_type  m_buttonCode;

    // m_Z is the mouse wheel
    Component::AxisRelAbs m_X, m_Y, m_Z;
  };

};};

namespace tloc { namespace input { namespace hid { namespace priv {

  ///-------------------------------------------------------------------------
  /// Mouse implementation that must be specialized for each platform
  ///
  /// \tparam T_ParentMouse Platform-independant mouse implementation that
  ///                          will eventually create platform-specific
  ///                          implementations
  ///-------------------------------------------------------------------------
  template <class T_ParentMouse> class MouseImpl;

  template <class T_ParentMouse, class T_ParamList>
  class MouseImplBase : public core::ImplBase<T_ParentMouse>
                      , public p_hid::Mouse
  {
  public:
    typedef core::ImplBase<T_ParentMouse>                 base_type;
    typedef typename base_type::parent_type               parent_type;

    typedef T_ParamList                                   param_list_type;
    typedef typename parent_type::platform_type           platform_type;
    typedef typename parent_type::button_code_type        button_code_type;
    typedef typename parent_type::size_type               size_type;
    typedef u32                                           index_type;

    MouseImplBase(parent_type* a_parent, param_list_type a_params)
      : base_type(a_parent), m_params(a_params)
    {
    }

    const param_list_type& GetParams() const
    {
      return m_params;
    }

  protected:

    param_list_type       m_params;
  };

};};};};

#endif