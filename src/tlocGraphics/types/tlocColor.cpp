#include "tlocColor.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/data_structures/tlocTuple.inl>

namespace tloc { namespace graphics { namespace types {

  namespace
  {
    const Color::value_type g_minValue = 0;
    const Color::value_type g_maxValue = 255;

    //------------------------------------------------------------------------
    // Converting color to a packged integer. Assuming a_colArray is an array
    // of four bytes in the order RGBA

    typedef Color::int_type   int_color_type;

    typedef type_true         byte_type_true;
    typedef type_false        real_type_true;

    namespace priv
    {
      template <typename T_Real>
      T_Real DoNormalizeColor(Color::value_type a_color)
      {
        using namespace core::utils;

        static T_Real oneDivMax
          = 1.0f / static_cast<T_Real>(g_maxValue);

        return static_cast<T_Real>(a_color) * oneDivMax;
      }

      Color::int_type DoGetAs(const Color::container_type& a_colArray,
                              p_color::format::RGBA)
      {
        int_color_type  retVal = 0;
        retVal |= a_colArray[Color::r] << 24;
        retVal |= a_colArray[Color::g] << 16;
        retVal |= a_colArray[Color::b] << 8;
        retVal |= a_colArray[Color::a];

        return retVal;
      }

      Color::int_type DoGetAs(const Color::container_type& a_colArray,
                              p_color::format::ABGR)
      {
        int_color_type  retVal = 0;
        retVal |= a_colArray[Color::a] << 24;
        retVal |= a_colArray[Color::b] << 16;
        retVal |= a_colArray[Color::g] << 8;
        retVal |= a_colArray[Color::r];

        return retVal;
      }

      Color::int_type DoGetAs(const Color::container_type& a_colArray,
                              p_color::format::ARGB)
      {
        int_color_type  retVal = 0;
        retVal |= a_colArray[Color::a] << 24;
        retVal |= a_colArray[Color::r] << 16;
        retVal |= a_colArray[Color::g] << 8;
        retVal |= a_colArray[Color::b];

        return retVal;
      }

      Color::int_type DoGetAs(const Color::container_type& a_colArray,
                              p_color::format::BGRA)
      {
        int_color_type  retVal = 0;
        retVal |= a_colArray[Color::b] << 24;
        retVal |= a_colArray[Color::g] << 16;
        retVal |= a_colArray[Color::r] << 8;
        retVal |= a_colArray[Color::a];

        return retVal;
      }

      template <typename T_VectorType>
      void DoGetAs(const Color::container_type& a_colArray,
                   T_VectorType& a_vecOut, p_color::format::RGBA)
      {
        typedef typename T_VectorType::value_type value_type;

        a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[Color::r]);
        a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[Color::g]);
        a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[Color::b]);
        a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[Color::a]);
      }

      template <typename T_VectorType>
      void DoGetAs(const Color::container_type& a_colArray,
                   T_VectorType& a_vecOut, p_color::format::ABGR)
      {
        typedef typename T_VectorType::value_type value_type;

        a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[Color::a]);
        a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[Color::b]);
        a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[Color::g]);
        a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[Color::r]);
      }

      template <typename T_VectorType>
      void DoGetAs(const Color::container_type& a_colArray,
                   T_VectorType& a_vecOut, p_color::format::ARGB)
      {
        typedef typename T_VectorType::value_type value_type;

        a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[Color::a]);
        a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[Color::r]);
        a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[Color::g]);
        a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[Color::b]);
      }

      template <typename T_VectorType>
      void DoGetAs(const Color::container_type& a_colArray,
                   T_VectorType& a_vecOut, p_color::format::BGRA)
      {
        typedef typename T_VectorType::value_type value_type;

        a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[Color::b]);
        a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[Color::g]);
        a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[Color::r]);
        a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[Color::a]);
      }

      template <typename T_Integer>
      void DoSetAs(T_Integer a_R, T_Integer a_G, T_Integer a_B, T_Integer a_A,
                   Color::container_type& a_out, byte_type_true)
      {
        a_out[0] = core::utils::CastNumber<Color::value_type>(a_R);
        a_out[1] = core::utils::CastNumber<Color::value_type>(a_G);
        a_out[2] = core::utils::CastNumber<Color::value_type>(a_B);
        a_out[3] = core::utils::CastNumber<Color::value_type>(a_A);
      }

      template <typename T_Real>
      void DoSetAs(T_Real a_R, T_Real a_G, T_Real a_B, T_Real a_A,
        Color::container_type& a_out,
        real_type_true)
      {
        typedef T_Real              real_type;
        typedef Color::value_type   value_type;

        real_type clamped[4] =
        {
          core::tlClamp<real_type>(a_R, 0, 1),
          core::tlClamp<real_type>(a_G, 0, 1),
          core::tlClamp<real_type>(a_B, 0, 1),
          core::tlClamp<real_type>(a_A, 0, 1),
        };

        a_out[0] = static_cast<value_type>(g_maxValue * clamped[0]);
        a_out[1] = static_cast<value_type>(g_maxValue * clamped[1]);
        a_out[2] = static_cast<value_type>(g_maxValue * clamped[2]);
        a_out[3] = static_cast<value_type>(g_maxValue * clamped[3]);
      }
    };
  };

  const Color Color::COLOR_BLACK = Color(0, 0, 0, 255);
  const Color Color::COLOR_WHITE = Color(255, 255, 255, 255);

  Color::Color() : m_rgba(0)
  { }

  template <typename T_ValueType>
  Color::Color(T_ValueType a_R, T_ValueType a_G,
               T_ValueType a_B, T_ValueType a_A)
  {
    SetAs(a_R, a_G, a_B, a_A);
  }

  template <typename T_ValueType>
  void Color::SetAs(T_ValueType a_R, T_ValueType a_G,
                    T_ValueType a_B, T_ValueType a_A)
  {
    typedef typename Loki::Select <
                                   Loki::TypeTraits<T_ValueType>::isFloat,
                                   real_type_true, byte_type_true
                                  >::Result  selected_type;

    priv::DoSetAs(a_R, a_G, a_B, a_A, m_rgba, selected_type() );
  }

  template <typename T_ColorFormat>
  Color::int_type Color::DoGetAs()
  {
    return priv::DoGetAs(m_rgba, T_ColorFormat());
  }

  template <typename T_ColorFormat, typename T_VectorType>
  void Color::DoGetAs(T_VectorType& a_vec)
  {
    priv::DoGetAs(m_rgba, a_vec, T_ColorFormat());
  }

  Color::value_type& Color::operator[](tl_int a_index)
  {
    return m_rgba[a_index];
  }

  const Color::value_type& Color::operator[](tl_int a_index) const
  {
    return m_rgba[a_index];
  }

  Color Color::operator +(const Color &a_other)
  {
    Color temp(*this);
    temp[0] += a_other[0];
    temp[1] += a_other[1];
    temp[2] += a_other[2];
    temp[3] += a_other[3];

    return temp;
  }

  Color& Color::operator +=(const Color &a_other)
  {
    m_rgba[0] += a_other[0];
    m_rgba[1] += a_other[1];
    m_rgba[2] += a_other[2];
    m_rgba[3] += a_other[3];

    return *this;
  }

  Color Color::operator *(const Color &a_other)
  {
    Color temp(*this);
    temp[0] *= a_other[0];
    temp[1] *= a_other[1];
    temp[2] *= a_other[2];
    temp[3] *= a_other[3];

    return temp;
  }

  Color& Color::operator *=(const Color &a_other)
  {
    m_rgba[0] *= a_other[0];
    m_rgba[1] *= a_other[1];
    m_rgba[2] *= a_other[2];
    m_rgba[3] *= a_other[3];

    return *this;
  }

  Color Color::operator -(const Color &a_other)
  {
    Color temp(*this);
    temp[0] -= a_other[0];
    temp[1] -= a_other[1];
    temp[2] -= a_other[2];
    temp[3] -= a_other[3];

    return temp;
  }

  Color& Color::operator -=(const Color &a_other)
  {
    m_rgba[0] -= a_other[0];
    m_rgba[1] -= a_other[1];
    m_rgba[2] -= a_other[2];
    m_rgba[3] -= a_other[3];

    return *this;
  }

  bool Color::operator ==(const Color &a_other)
  {
    return ( m_rgba[0] == a_other[0] &&
             m_rgba[1] == a_other[1] &&
             m_rgba[2] == a_other[2] &&
             m_rgba[3] == a_other[3] );
  }

  bool Color::operator !=(const Color &a_other)
  {
    return !operator==(a_other);
  }

  //------------------------------------------------------------------------
  // Explicit initialization

  using namespace tloc::math::types;

  template int_color_type Color::DoGetAs<p_color::format::RGBA>();
  template int_color_type Color::DoGetAs<p_color::format::ABGR>();
  template int_color_type Color::DoGetAs<p_color::format::ARGB>();
  template int_color_type Color::DoGetAs<p_color::format::BGRA>();

  template Color::Color(u8, u8, u8, u8);
  template Color::Color(f32, f32, f32, f32);
  template Color::Color(f64, f64, f64, f64);

  template void Color::SetAs(u8, u8, u8, u8);
  template void Color::SetAs(f32, f32, f32, f32);
  template void Color::SetAs(f64, f64, f64, f64);

#define TLOC_INSTANTIATE_COLOR_GET_AS(_type_)\
  template void Color::DoGetAs<p_color::format::RGBA, _type_>(_type_&);\
  template void Color::DoGetAs<p_color::format::ABGR, _type_>(_type_&);\
  template void Color::DoGetAs<p_color::format::ARGB, _type_>(_type_&);\
  template void Color::DoGetAs<p_color::format::BGRA, _type_>(_type_&)

  TLOC_INSTANTIATE_COLOR_GET_AS(Vec4f32);
  TLOC_INSTANTIATE_COLOR_GET_AS(Vec4f64);

#undef TLOC_INSTANTIATE_COLOR_GET_AS

};};};