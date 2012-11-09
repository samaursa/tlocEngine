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
    typedef tl_float                real_type;

  public:
    Color();

    template <typename T_ValueType>
    Color(T_ValueType a_R, T_ValueType a_G, T_ValueType a_B, T_ValueType a_A);

    template <typename T_ColorFormat>
    int_type GetAs();

    template <typename T_ColorFormat, typename T_VectorType>
    void     GetAs(T_VectorType& a_vec);

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

    static const Color COLOR_BLACK;
    static const Color COLOR_WHITE;

  private:
    container_type      m_rgba;
  };

};};};

#endif