#ifndef TLOC_INPUT_TYPES_H
#define TLOC_INPUT_TYPES_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace input {

  namespace InputPolicy
  {
    struct Buffered{};
    struct Immediate{};
  };

  namespace p_hid
  {
    struct HIDType      {};

    struct Keyboard     : public HIDType { static const int m_index = 0; };
    struct Mouse        : public HIDType { static const int m_index = 1; };
    struct Joystick     : public HIDType { static const int m_index = 2; };
    struct TouchSurface : public HIDType { static const int m_index = 3; };

    struct Count                         { static const int m_index = 4; };

    template <typename T_InputObject>
    void IsInputTypeSupported()
    {
#ifndef TLOC_OS_IPHONE // see changelog for why we have to do this
      TLOC_STATIC_ASSERT(
        (Loki::Conversion<T_InputObject, p_hid::HIDType>::exists),
        Object_must_be_HID_type);
#endif
    }
  }

  namespace param_options
  {
    enum
    {
      // Useful only for windows
      TL_WIN_DISCL_BACKGROUND   = 1 << 0,
      TL_WIN_DISCL_EXCLUSIVE    = 1 << 1,
      TL_WIN_DISCL_FOREGROUND   = 1 << 2,
      TL_WIN_DISCL_NONEXCLUSIVE = 1 << 3,
      TL_WIN_DISCL_NOWINKEY     = 1 << 4,

      TL_WIN_DISCL_DEFAULT = TL_WIN_DISCL_FOREGROUND |
                             TL_WIN_DISCL_NONEXCLUSIVE,

      k_count = core::utils::EnumCounter<TL_WIN_DISCL_NOWINKEY, true>::result,
    }; typedef tl_int value_type;
  }

  namespace buffer_size
  {
    enum Sizes
    {
      keyboard_buffer_size      = 17,
      mouse_buffer_size         = 128,
      joystick_buffer_Size      = 129,
      touch_surface_buffer_size = 256,
    };
  }

  //------------------------------------------------------------------------
  // Components
  namespace Component
  {
    // In OIS these are enums, we go a different route, although the idea of
    // components is taken from OIS
    namespace p_type
    {
      struct Button {};
      struct Axis {};
      struct Slider {};
      struct Vector3 {};
    };

    namespace p_axis
    {
      struct RelativeOnly{};
      struct AbsoluteOnly{};
      struct RelativeAndAbsolute{};
    };

    // Base component type
    template <typename T_ComponentType,
              typename T_PolicyType = p_axis::RelativeAndAbsolute,
              typename T_ValueType = void> struct Type;

    template<>
    struct Type<p_type::Button>
    {
      Type(bool a_pressed = false) : m_pressed(a_pressed) {}

      bool m_pressed;
    };

    template <typename T_PolicyType, typename T_ValueType>
    struct Type<p_type::Axis, T_PolicyType, T_ValueType>
    {
    public:

      typedef Type<p_type::Axis, T_PolicyType, T_ValueType>   this_type;

      typedef T_PolicyType                                    policy_type;
      typedef T_ValueType                                     value_type;

      typedef typename
        Loki::Int2Type<Loki::IsSameType<policy_type,
        p_axis::RelativeAndAbsolute>::value>                  policy_result_type;

      // Relative and absolute types
      typedef core::ConditionalTypePackage
              <value_type, value_type,
               policy_result_type::value>                     rel_and_abs;
      typedef value_type                                      rel_type;
      typedef typename rel_and_abs::cond_type                 abs_type;

      Type(value_type a_abs = 0, value_type a_rel = 0)
      {
        m_abs() = a_abs; m_rel() = a_rel;
      }

      Type(const this_type& a_other)
      {
        m_absoluteAndRelative = a_other.m_absoluteAndRelative;
        m_absoluteAndRelative.m_var = a_other.m_absoluteAndRelative.m_var;
      }

      this_type& operator= (const this_type& a_other)
      {
        m_absoluteAndRelative = a_other.m_absoluteAndRelative;
        m_absoluteAndRelative.m_var = a_other.m_absoluteAndRelative.m_var;

        return *this;
      }

      TL_FI rel_type&       m_rel()
      { return m_absoluteAndRelative.m_var; }
      TL_FI const rel_type& m_rel() const
      { return m_absoluteAndRelative.m_var; }
      TL_FI abs_type&       m_abs()
      { return (abs_type&)m_absoluteAndRelative; }
      TL_FI const abs_type& m_abs() const
      { return (abs_type&)m_absoluteAndRelative; }

    protected:
      rel_and_abs m_absoluteAndRelative;
    };


    template <typename T_ValueType>
    struct Type<p_type::Axis, p_axis::AbsoluteOnly, T_ValueType>
      : public Type<p_type::Axis, p_axis::RelativeOnly, T_ValueType>
    {
    public:
      typedef
        Type<p_type::Axis, p_axis::AbsoluteOnly, T_ValueType>  this_type;

      typedef
        Type<p_type::Axis, p_axis::RelativeOnly, T_ValueType>  base_type;

      typedef typename base_type::value_type                    value_type;

      typedef p_axis::AbsoluteOnly                              policy_type;

      typedef typename base_type::rel_and_abs                   rel_and_abs;

      // Note: These are intentionally switched, as base_type::abs_type does not
      // "exist" due to the conditional type.
      typedef typename base_type::rel_type                      abs_type;
      typedef typename base_type::abs_type                      rel_type;

      using base_type::m_absoluteAndRelative;

      Type(value_type a_abs = 0, value_type a_rel = 0)
        : base_type(a_abs, a_rel)
      {
        m_abs() = a_abs; m_rel() = a_rel;
      }

      Type(const this_type& a_other)
        : base_type(a_other)
      { }

      TL_FI rel_type&       m_rel()
      { return (rel_type&)m_absoluteAndRelative; }
      TL_FI const rel_type& m_rel() const
      { return (rel_type&)m_absoluteAndRelative; }
      TL_FI abs_type&       m_abs()
      { return m_absoluteAndRelative.m_var; }
      TL_FI const abs_type& m_abs() const
      { return m_absoluteAndRelative.m_var; }
    };

    typedef Type<p_type::Button>     Button;
    typedef Type<p_type::Axis, p_axis::RelativeOnly, tl_int>         AxisRel;
    typedef Type<p_type::Axis, p_axis::AbsoluteOnly, tl_int>         AxisAbs;
    typedef Type<p_type::Axis, p_axis::RelativeAndAbsolute, tl_int>  AxisRelAbs;
    typedef Type<p_type::Axis, p_axis::RelativeOnly, tl_float>         AxisRelf;
    typedef Type<p_type::Axis, p_axis::AbsoluteOnly, tl_float>         AxisAbsf;
    typedef Type<p_type::Axis, p_axis::RelativeAndAbsolute, tl_float>  AxisRelAbsf;
    //typedef Type<Slider>  Slider;
    //typedef Type<Vector3> Vector3;
  }

};};

#endif