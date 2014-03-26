#ifndef TLOC_GRAPHICS_TYPES_COLOR_H
#define TLOC_GRAPHICS_TYPES_COLOR_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace graphics { namespace types {

  namespace p_color
  {
    struct Float{};
    struct Byte{};

    namespace format
    {
      struct RGBA{}; // the most common format
      struct ABGR{};
      struct ARGB{};
      struct BGRA{};
    };
  };

  class Color
  {
  public:
    enum
    {
      r = 0,
      g,
      b,
      a,
      channel_count
    }; typedef tl_size              channel_type;

    typedef u8                                value_type;
    typedef core::data_structs::Tuple<u8, 4>  container_type;
    typedef u32                               int_type;
    typedef tl_float                          real_type;

  public:
    Color();

    template <typename T_ValueType>
    Color(T_ValueType a_R, T_ValueType a_G, T_ValueType a_B, T_ValueType a_A);

    template <typename T_ValueType>
    void SetAs(T_ValueType a_R, T_ValueType a_G, T_ValueType a_B,
               T_ValueType a_A);

    template <typename T_ColorFormat>
    int_type GetAs() const
    {
      using namespace p_color::format;
      type_traits::AssertTypeIsSupported
        <T_ColorFormat, RGBA, ABGR, ARGB, BGRA>();

      return DoGetAs<T_ColorFormat>();
    }

    template <typename T_ColorFormat, typename T_VectorType>
    T_VectorType GetAs() const
    {
      T_VectorType v;
      GetAs<T_ColorFormat>(v);
      return v;
    }

    template <typename T_ColorFormat, typename T_VectorType>
    void     GetAs(T_VectorType& a_vec) const
    {
      using namespace p_color::format;
      using tloc::math::types::Vec4f32;
      using tloc::math::types::Vec4f64;

      type_traits::AssertTypeIsSupported
        <T_ColorFormat, RGBA, ABGR, ARGB, BGRA>();

      type_traits::AssertTypeIsSupported
        <T_VectorType, Vec4f32, Vec4f64>();

      DoGetAs<T_ColorFormat>(a_vec);
    }

    value_type&       operator[](tl_int a_index);
    const value_type& operator[](tl_int a_index) const;

    Color   operator + (const Color& a_other) const;
    Color&  operator +=(const Color& a_other);
    Color   operator * (const Color& a_other) const;
    Color&  operator *=(const Color& a_other);
    Color   operator - (const Color& a_other) const;
    Color&  operator -=(const Color& a_other);

    bool    operator ==(const Color& a_other) const;
    bool    operator !=(const Color& a_other) const;

    TLOC_DECL_AND_DEF_GETTER(container_type, Get, m_rgba);

  public:
    static const Color COLOR_BLACK;
    static const Color COLOR_WHITE;

  private:
    template <typename T_ColorFormat>
    int_type DoGetAs() const;

    template <typename T_ColorFormat, typename T_VectorType>
    void DoGetAs(T_VectorType& a_vec) const;

    template <typename T_ValueType>
    void DoSetAs(T_ValueType a_R, T_ValueType a_G, T_ValueType a_B,
                 T_ValueType a_A);

    container_type      m_rgba;
  };

  //--
  // Template definitions

  template <typename T_ValueType>
  void Color::SetAs(T_ValueType a_R, T_ValueType a_G, T_ValueType a_B,
                    T_ValueType a_A)
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T_ValueType);
    DoSetAs(a_R, a_G, a_B, a_A);
  }


};};};

#endif