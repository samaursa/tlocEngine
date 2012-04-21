#ifndef TLOC_INPUT_TYPES_H
#define TLOC_INPUT_TYPES_H

#include "tlocCore/tlocTypeTraits.h"
#include "tlocCore/tlocUtils.h"

namespace tloc { namespace input {

  namespace InputPolicy
  {
    struct Buffered{};
    struct Immediate{};
  };

  namespace hid
  {
    enum Type
    {
      keyboard = 0,
      mouse,
      joystick,

      count
    };
  }

  namespace parameter_options
  {
    enum Type
    {
      TL_DEFAULT = 0,

      // Useful only for windows
      TL_WIN_DISCL_BACKGROUND   = 1 << 0,
      TL_WIN_DISCL_EXCLUSIVE    = 1 << 1,
      TL_WIN_DISCL_FOREGROUND   = 1 << 2,
      TL_WIN_DISCL_NONEXCLUSIVE = 1 << 3,
      TL_WIN_DISCL_NOWINKEY     = 1 << 4,

      count = core::EnumCounter<TL_WIN_DISCL_NOWINKEY, true>::result,
    };
  }

  namespace buffer_size
  {
    enum Sizes
    {
      keyboard_buffer_size = 17,
      mouse_buffer_size    = 128,
      joystick_buffer_Size = 129
    };
  }

  //------------------------------------------------------------------------
  // Components
  namespace Component
  {
    // In OIS these are enums, we go a different route, although the idea of
    // components is taken from OIS
    namespace Policy
    {
      struct Button {};
      struct Axis {};
      struct Slider {};
      struct Vector3 {};
    };

    // Base component type
    template <typename T_ComponentType, bool T_AbsOnly = false,
              typename T_ValueType = void> struct Type;

    template<>
    struct Type<Policy::Button>
    {
      Type(bool a_pressed = false) : m_pressed(a_pressed) {}

      bool m_pressed;
    };

    template<bool T_AbsOnly, typename T_ValueType>
    struct Type<Policy::Axis, T_AbsOnly, T_ValueType>
    {
      typedef Loki::Select<T_AbsOnly, type_true, type_false>  abs_only_type;
      typedef T_ValueType                                     value_type;
      // Relative and absolute types
      typedef ConditionalTypePackage<value_type, value_type, T_AbsOnly>
                                                              abs_and_rel;
      typedef typename abs_and_rel::cond_type                 relative_type;

      Type(value_type a_abs = 0, value_type a_rel = 0)
      {
        m_abs() = a_abs; m_rel() = a_rel;
      }

      TL_FI value_type&       m_abs()
      { return m_absoluteAndRelative.m_var; }
      TL_FI const value_type& m_abs() const
      { return m_absoluteAndRelative.m_var; }
      TL_FI relative_type&    m_rel()
      { return (relative_type&)m_absoluteAndRelative; }
      TL_FI const relative_type& m_rel() const
      { return (relative_type&)m_absoluteAndRelative; }

    private:
      abs_and_rel m_absoluteAndRelative;
    };

    typedef Type<Policy::Button>     Button;
    typedef Type<Policy::Axis, false, s64>     AxisAbs;
    typedef Type<Policy::Axis, true, s64>      AxisAbsRel;
    typedef Type<Policy::Axis, false, f64>     AxisAbsf;
    typedef Type<Policy::Axis, true, f64>      AxisAbsRelf;
    //typedef Type<Slider>  Slider;
    //typedef Type<Vector3> Vector3;
  }

};};

#endif