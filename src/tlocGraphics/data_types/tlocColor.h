#ifndef TLOC_GRAPHICS_TYPES_COLOR_H
#define TLOC_GRAPHICS_TYPES_COLOR_H

#include <tlocCore/data_structures/tlocTuple.h>

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

    typedef u8                      value_type;
    typedef core::Tuple<u8, 4>      container_type;
    typedef u32                     int_type;
    typedef tl_float                float_type;

  public:
    Color();
    Color(value_type a_R,
          value_type a_G,
          value_type a_B,
          value_type a_A);

    Color(float_type a_R,
          float_type a_G,
          float_type a_B,
          float_type a_A, p_color::Float);

    template <typename T_ColorFormat>
    int_type GetAs();

    value_type&       operator[](tl_int a_index);
    const value_type& operator[](tl_int a_index) const;

    Color   operator + (const Color& a_other);
    Color&  operator +=(const Color& a_other);
    Color   operator * (const Color& a_other);
    Color&  operator *=(const Color& a_other);
    Color   operator - (const Color& a_other);
    Color&  operator -=(const Color& a_other);

    bool    operator ==(const Color& a_other);
    bool    operator !=(const Color& a_other);

  private:
    container_type      m_rgba;
  };

};};};

#endif