#ifndef TLOC_INPUT_TYPES_H
#define TLOC_INPUT_TYPES_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

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

      k_count = core::utils::EnumCounter_T<TL_WIN_DISCL_NOWINKEY, true>::result,
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

    // ///////////////////////////////////////////////////////////////////////
    // Axis_T<>

    template <typename T_PolicyType, typename T_ValueType>
    struct Axis_T;

    // ///////////////////////////////////////////////////////////////////////

    template <typename T_ValueType>
    struct Axis_T<p_axis::RelativeOnly, T_ValueType>
    {
    public:
      typedef T_ValueType                             value_type;
      typedef value_type                              rel_type;
      typedef value_type                              abs_type;

    public:
      Axis_T(value_type = 0, value_type a_rel = 0) : m_rel(a_rel) { }

    public:
      value_type m_rel;
    };

    // ///////////////////////////////////////////////////////////////////////

    template <typename T_ValueType>
    struct Axis_T<p_axis::AbsoluteOnly, T_ValueType>
    {
    public:
      typedef T_ValueType                             value_type;
      typedef value_type                              rel_type;
      typedef value_type                              abs_type;

    public:
      Axis_T(value_type a_abs = 0, value_type = 0) : m_abs(a_abs) { }

    public:
      value_type m_abs;
    };

    // ///////////////////////////////////////////////////////////////////////

    template <typename T_ValueType>
    struct Axis_T<p_axis::RelativeAndAbsolute, T_ValueType>
    {
    public:
      typedef T_ValueType                             value_type;
      typedef value_type                              rel_type;
      typedef value_type                              abs_type;

    public:
      Axis_T(value_type a_abs = 0, value_type a_rel = 0) 
        : m_abs(a_abs), m_rel(a_rel) { }

    public:
      value_type m_rel;
      value_type m_abs;
    };

    // ///////////////////////////////////////////////////////////////////////
    // Generic axis type

    // Base component type
    template <typename T_ComponentType,
              typename T_PolicyType = p_axis::RelativeAndAbsolute,
              typename T_ValueType = void> struct Type_T;

    template<>
    struct Type_T<p_type::Button, p_axis::RelativeAndAbsolute, int>
    {
      Type_T(bool a_pressed = false) : m_pressed(a_pressed) {}

      bool m_pressed;
    };

    template <typename T_PolicyType, typename T_ValueType>
    struct Type_T<p_type::Axis, T_PolicyType, T_ValueType>
      : public Axis_T<T_PolicyType, T_ValueType>
    {
    public:

      typedef Type_T<p_type::Axis, T_PolicyType, T_ValueType>   this_type;

      typedef T_PolicyType                                    policy_type;
      typedef T_ValueType                                     value_type;

      typedef typename
        Loki::Int2Type<Loki::IsSameType<policy_type,
        p_axis::RelativeAndAbsolute>::value>                  policy_result_type;

      typedef Axis_T<policy_type, value_type>                 base_type;
      typedef value_type                                      rel_type;
      typedef value_type                                      abs_type;

      Type_T(value_type a_abs = 0, value_type a_rel = 0)
        : base_type(a_abs, a_rel)
      { }
    };

    // -----------------------------------------------------------------------
    // typedefs

    typedef Type_T<p_type::Button>     Button;
    typedef Type_T<p_type::Axis, p_axis::RelativeOnly, tl_int>         AxisRel;
    typedef Type_T<p_type::Axis, p_axis::AbsoluteOnly, tl_int>         AxisAbs;
    typedef Type_T<p_type::Axis, p_axis::RelativeAndAbsolute, tl_int>  AxisRelAbs;
    typedef Type_T<p_type::Axis, p_axis::RelativeOnly, tl_float>         AxisRelf;
    typedef Type_T<p_type::Axis, p_axis::AbsoluteOnly, tl_float>         AxisAbsf;
    typedef Type_T<p_type::Axis, p_axis::RelativeAndAbsolute, tl_float>  AxisRelAbsf;
    //typedef Type<Slider>  Slider;
    //typedef Type<Vector3> Vector3;

    // ///////////////////////////////////////////////////////////////////////
    // Point of view
    struct Pov
    {
    public:
      enum
      {
        k_centered    = 0,
        k_north       = 1 << 0,
        k_south       = 1 << 1,
        k_east        = 1 << 2,
        k_west        = 1 << 3,
        k_north_east  = 1 << 4,
        k_south_east  = 1 << 5,
        k_north_west  = 1 << 6,
        k_south_west  = 1 << 7,

        k_count = core_utils::EnumCounter_T<k_south_west, true>::result
      }; typedef tl_int direction_type;

      TLOC_DECL_AND_DEF_SETTER_BY_VALUE(direction_type, SetDirection, m_direction);
      TLOC_DECL_AND_DEF_GETTER(direction_type, GetDirection, m_direction);

      bool        IsDirection(direction_type a_dir) const;
      const char* GetDirectionAsString(direction_type a_dir) const;
      const char* GetDirectionAsShortString(direction_type a_dir) const;

    private:
      direction_type      m_direction;

      static const char*  s_enumStrings[];
      static const char*  s_enumStringsShort[];
    };
  }

};};

#endif