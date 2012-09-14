#include "tlocColor.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
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
  };

  Color::Color()
    : m_rgba(0)
  {
  }

  Color::Color(value_type a_R, value_type a_G, value_type a_B,
               value_type a_A)
  {
    m_rgba[0] = a_R;
    m_rgba[1] = a_G;
    m_rgba[2] = a_B;
    m_rgba[3] = a_A;
  }

  Color::Color(float_type a_R, float_type a_G, float_type a_B,
               float_type a_A, p_color::Float)
  {
    float_type clamped[4] =
    {
      core::tlClamp<float_type>(a_R, 0, 1),
      core::tlClamp<float_type>(a_G, 0, 1),
      core::tlClamp<float_type>(a_B, 0, 1),
      core::tlClamp<float_type>(a_A, 0, 1),
    };

    m_rgba[0] = static_cast<value_type>(g_maxValue * clamped[0]);
    m_rgba[1] = static_cast<value_type>(g_maxValue * clamped[1]);
    m_rgba[2] = static_cast<value_type>(g_maxValue * clamped[2]);
    m_rgba[3] = static_cast<value_type>(g_maxValue * clamped[3]);
  }

  template <typename T_ColorFormat>
  Color::int_type Color::GetAs()
  {
    return DoGetAs(m_rgba, T_ColorFormat());
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

  template int_color_type Color::GetAs<p_color::format::RGBA>();
  template int_color_type Color::GetAs<p_color::format::ABGR>();
  template int_color_type Color::GetAs<p_color::format::ARGB>();
  template int_color_type Color::GetAs<p_color::format::BGRA>();

};};};