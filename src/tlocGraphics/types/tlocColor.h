#ifndef TLOC_GRAPHICS_TYPES_COLOR_H
#define TLOC_GRAPHICS_TYPES_COLOR_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/tlocRange.h>

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

  // ///////////////////////////////////////////////////////////////////////
  // Color_TI

  namespace p_color
  {
    namespace channel
    {
      enum
      {
        r = 0,
        g,
        b,
        a,
        channel_count
      }; typedef tl_size              channel_type;
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Empty base class to distinguish Color_TI from other types

  namespace priv {
    class ColorType
    {
      template <class T, class U> friend struct Loki::Conversion;

    protected:
      ColorType() {}
      ~ColorType() {}
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Color_TI<>

  template <typename T, tl_int T_Size>
  class Color_TI
    : public gfx_t::priv::ColorType
  {
    TLOC_STATIC_ASSERT(T_Size >= 0 && T_Size <= 4, Unsupported_color_size_requested);
    TLOC_STATIC_ASSERT( (Loki::IsSameType<T, u8>::value ||
                         Loki::IsSameType<T, u16>::value ||
                         Loki::IsSameType<T, f32>::value), Unsupported_color_type);

  public:
    enum { k_size = T_Size };
    enum { k_channels = k_size };

  public:
    typedef T                                             value_type;
    typedef core_sptr::VirtualPtr<value_type>             value_type_ptr;
    typedef core_sptr::VirtualPtr<const value_type>       const_value_type_ptr;
    typedef Color_TI<value_type, k_size>                  this_type;
    typedef core_ds::Tuple<value_type, k_size>            color_type;
    typedef typename color_type::size_type                size_type;
    typedef u32                                           int_type;
    typedef tl_float                                      real_type;

  public:
    Color_TI();

    template <typename U>
    Color_TI(const Color_TI<U, T_Size>& a_other);

    template <typename U>
    explicit Color_TI(const core_ds::Tuple<U, k_size>& a_colorByChannels);

    template <typename U>
    void          SetAs(const core_ds::Tuple<U, k_size>& a_colorInChannels);

    template <typename T_ColorFormat>
    int_type      GetAs() const;

    template <typename T_ColorFormat, typename T_VectorType>
    T_VectorType  GetAs() const;

    template <typename T_ColorFormat, typename T_VectorType>
    void          GetAs(T_VectorType& a_vec) const;

    value_type_ptr          get();
    const_value_type_ptr    get() const;

    value_type&       operator[](tl_int a_index);
    const value_type& operator[](tl_int a_index) const;

    this_type   operator + (const this_type& a_other) const;
    this_type&  operator +=(const this_type& a_other);
    this_type   operator * (const this_type& a_other) const;
    this_type&  operator *=(const this_type& a_other);
    this_type   operator - (const this_type& a_other) const;
    this_type&  operator -=(const this_type& a_other);

    this_type   operator * (real_type a_multi) const;
    this_type&  operator *=(real_type a_multi);
    this_type   operator / (real_type a_multi) const;
    this_type&  operator /=(real_type a_multi);

    bool        operator ==(const this_type& a_other) const;
    bool        operator !=(const this_type& a_other) const;

    TLOC_DECL_AND_DEF_GETTER(color_type, Get, m_color);

  private:
    template <typename T_ColorFormat>
    int_type DoGetAs() const;

    template <typename T_ColorFormat, typename T_VectorType>
    void DoGetAs(T_VectorType& a_vec) const;

    //template <typename T_ColorFormat, typename T_VectorType>
    //T_VectorType DoGetAs() const;

    template <typename U>
    void DoSetAs(const core_ds::Tuple<U, k_size>& a_colorByChannels);

  private:
    color_type      m_color;
  };

  // -----------------------------------------------------------------------
  // Template definitions

  template <typename T, tl_int T_Size>
  template <typename U>
  Color_TI<T, T_Size>::
    Color_TI(const Color_TI<U, T_Size>& a_other)
  {
    SetAs(a_other.Get());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_int T_Size>
  template <typename U>
  Color_TI<T, T_Size>::
    Color_TI(const core_ds::Tuple<U, k_size>& a_colorByChannels)
  {
    SetAs(a_colorByChannels);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_int T_Size>
  template <typename U>
  void
  Color_TI<T, T_Size>::
    SetAs(const core_ds::Tuple<U, k_size>& a_colorInChannels)
  {
    tloc::type_traits::AssertTypeIsSupported
      <U, u8, s32, s64, f32, f64>();

    DoSetAs(a_colorInChannels);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_int T_Size>
  template <typename T_ColorFormat>
  typename Color_TI<T, T_Size>::int_type
    Color_TI<T, T_Size>::
    GetAs() const
  {
    using namespace p_color::format;
    tloc::type_traits::AssertTypeIsSupported
      <T_ColorFormat, RGBA, ABGR, ARGB, BGRA>();

    return DoGetAs<T_ColorFormat>();
  }


  template <typename T, tl_int T_Size>
  template <typename T_ColorFormat, typename T_VectorType>
  T_VectorType
    Color_TI<T, T_Size>::
    GetAs() const
  {
    TLOC_STATIC_ASSERT( (T_VectorType::k_size == k_size),
      Selected_vector_cannot_contain_color_type);

    type_traits::AssertTypeIsSupported
      <T_VectorType,
      core_ds::Tuple<u8, k_size>, core_ds::Tuple<u16, k_size>,
      math_t::Vec2f32, math_t::Vec3f32, math_t::Vec4f32>();

    T_VectorType v;
    GetAs<T_ColorFormat>(v);
    return v;
  }

  template <typename T, tl_int T_Size>
  template <typename T_ColorFormat, typename T_VectorType>
  void
    Color_TI<T, T_Size>::
    GetAs(T_VectorType& a_vec) const
  {
    using namespace p_color::format;
    using tloc::math::types::Vec4f32;
    using tloc::math::types::Vec4f64;

    tloc::type_traits::AssertTypeIsSupported
      <T_ColorFormat, RGBA, ABGR, ARGB, BGRA>();

    tloc::type_traits::AssertTypeIsSupported
      <T_VectorType,
      core_ds::Tuple<u8, k_size>, core_ds::Tuple<u16, k_size>,
      core_ds::Tuple<f32, k_size>, core_ds::Tuple<f64, k_size>,
      math_t::Vector_T<f32, k_size>, math_t::Vector_T<f64, k_size> 
      >();

    DoGetAs<T_ColorFormat>(a_vec);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Color with specializations

  template <typename T, tl_int T_Size>
  class Color_T;

  // ///////////////////////////////////////////////////////////////////////
  // Color<T, 4>

  template <typename T>
  class Color_T<T, 4>
    : public Color_TI<T, 4>
  {
  public:
    typedef T                                             value_type;
    typedef Color_T<value_type, 4>                        this_type;
    typedef Color_TI<value_type, 4>                       base_type;

    typedef typename base_type::color_type                         color_type;
    typedef typename base_type::size_type                          size_type;
    typedef typename base_type::int_type                           int_type;
    typedef typename base_type::real_type                          real_type;
    
    enum { k_size = base_type::k_size };

  public:
    Color_T()
      : base_type()
    { }

    Color_T(const base_type& a_other)
      : base_type(a_other)
    { }

    template <typename U>
    explicit Color_T(const core_ds::Tuple<U, k_size>& a_colorByChannels)
      : base_type(a_colorByChannels)
    { }

    template <typename U>
    explicit Color_T(U r, U g, U b, U a)
      : base_type(core_ds::MakeTuple(r, g, b, a))
    { }

    template <typename U>
    void             SetAs(U r, U g, U b, U a)
    { base_type::SetAs(core_ds::MakeTuple(r, g, b, a)); }

    using base_type::SetAs;
    using base_type::GetAs;

    using base_type::operator[];
    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator-;
    using base_type::operator-=;

    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator==;
    using base_type::operator!=;

    using base_type::Get;

  public:
    static const this_type COLOR_BLACK;
    static const this_type COLOR_GREY;
    static const this_type COLOR_WHITE;
    static const this_type COLOR_RED;
    static const this_type COLOR_GREEN;
    static const this_type COLOR_BLUE;
    static const this_type COLOR_YELLOW;
    static const this_type COLOR_CYAN;
    static const this_type COLOR_MAGENTA;
  };

  // -----------------------------------------------------------------------
  // static variables

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_BLACK = Color_T<T, 4>(0, 0, 0, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_GREY = Color_T<T, 4>(128, 128, 128, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_WHITE = Color_T<T, 4>(255, 255, 255, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_RED = Color_T<T, 4>(255, 0, 0, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_GREEN = Color_T<T, 4>(0, 255, 0, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_BLUE = Color_T<T, 4>(0, 0, 255, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_YELLOW = Color_T<T, 4>(255, 255, 0, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_CYAN = Color_T<T, 4>(0, 255, 255, 255);

  template <typename T>
  const Color_T<T, 4>
    Color_T<T, 4>::COLOR_MAGENTA = Color_T<T, 4>(255, 0, 255, 255);

  // ///////////////////////////////////////////////////////////////////////
  // Color<T, 3>

  template <typename T>
  class Color_T<T, 3>
    : public Color_TI<T, 3>
  {
  public:
    typedef T                                             value_type;
    typedef Color_TI<value_type, 3>                       base_type;
    
    typedef typename base_type::color_type                color_type;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::int_type                  int_type;
    typedef typename base_type::real_type                 real_type;
    
    enum { k_size = base_type::k_size };
    
    typedef Color_T<value_type, k_size>                   this_type;

  public:
    Color_T()
      : base_type()
    { }

    Color_T(const base_type& a_other)
      : base_type(a_other)
    { }

    template <typename U>
    explicit Color_T(const core_ds::Tuple<U, k_size>& a_colorByChannels)
      : base_type(a_colorByChannels)
    { }

    template <typename U>
    explicit Color_T(U r, U g, U b)
      : base_type(core_ds::MakeTuple(r, g, b))
    { }

    template <typename U>
    void             SetAs(U r, U g, U b)
    { base_type::SetAs(core_ds::MakeTuple(r, g, b)); }

    using base_type::SetAs;
    using base_type::GetAs;

    using base_type::operator[];
    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator-;
    using base_type::operator-=;

    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator==;
    using base_type::operator!=;

    using base_type::Get;

  public:
    static const this_type COLOR_BLACK;
    static const this_type COLOR_GREY;
    static const this_type COLOR_WHITE;
    static const this_type COLOR_RED;
    static const this_type COLOR_GREEN;
    static const this_type COLOR_BLUE;
    static const this_type COLOR_YELLOW;
    static const this_type COLOR_CYAN;
    static const this_type COLOR_MAGENTA;
  };

  // -----------------------------------------------------------------------
  // static variables

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_BLACK = Color_T<T, 3>(0, 0, 0);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_GREY = Color_T<T, 3>(128, 128, 128);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_WHITE = Color_T<T, 3>(255, 255, 255);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_RED = Color_T<T, 3>(255, 0, 0);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_GREEN = Color_T<T, 3>(0, 255, 0);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_BLUE = Color_T<T, 3>(0, 0, 255);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_YELLOW = Color_T<T, 3>(255, 255, 0);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_CYAN = Color_T<T, 3>(0, 255, 255);

  template <typename T>
  const typename Color_T<T, 3>::this_type
    Color_T<T, 3>::COLOR_MAGENTA = Color_T<T, 3>(255, 0, 255);

  // ///////////////////////////////////////////////////////////////////////
  // Color<T, 2>

  template <typename T>
  class Color_T<T, 2>
    : public Color_TI<T, 2>
  {
  public:
    typedef T                                             value_type;
    typedef Color_TI<value_type, 2>                       base_type;

    typedef typename base_type::color_type                color_type;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::int_type                  int_type;
    typedef typename base_type::real_type                 real_type;
    
    enum { k_size = base_type::k_size };
    
    typedef Color_T<value_type, k_size>                   this_type;

  public:
    Color_T()
      : base_type()
    { }

    Color_T(const base_type& a_other)
      : base_type(a_other)
    { }

    template <typename U>
    explicit Color_T(const core_ds::Tuple<U, k_size>& a_colorByChannels)
      : base_type(a_colorByChannels)
    { }

    template <typename U>
    explicit Color_T(U r, U g)
      : base_type(core_ds::MakeTuple(r, g))
    { }

    template <typename U>
    void             SetAs(U r, U g)
    { base_type::SetAs(core_ds::MakeTuple(r, g)); }

    using base_type::SetAs;
    using base_type::GetAs;

    using base_type::operator[];
    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator-;
    using base_type::operator-=;

    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator==;
    using base_type::operator!=;

    using base_type::Get;

  public:
    static const this_type COLOR_BLACK;
    static const this_type COLOR_RED;
    static const this_type COLOR_GREEN;
    static const this_type COLOR_YELLOW;
  };

  // -----------------------------------------------------------------------
  // static variables

  template <typename T>
  const typename Color_T<T, 2>::this_type
    Color_T<T, 2>::COLOR_BLACK = Color_T<T, 2>(0, 0);

  template <typename T>
  const typename Color_T<T, 2>::this_type
    Color_T<T, 2>::COLOR_RED = Color_T<T, 2>(255, 0);

  template <typename T>
  const typename Color_T<T, 2>::this_type
    Color_T<T, 2>::COLOR_GREEN = Color_T<T, 2>(0, 255); 

  template <typename T>
  const typename Color_T<T, 2>::this_type
    Color_T<T, 2>::COLOR_YELLOW = Color_T<T, 2>(255, 255); 

  // ///////////////////////////////////////////////////////////////////////
  // Color<T, 1>

  template <typename T>
  class Color_T<T, 1>
    : public Color_TI<T, 1>
  {
  public:
    typedef T                                             value_type;
    typedef Color_TI<value_type, 1>                       base_type;

    typedef typename base_type::color_type                color_type;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::int_type                  int_type;
    typedef typename base_type::real_type                 real_type;
    
    enum { k_size = base_type::k_size };
    
    typedef Color_T<value_type, k_size>                   this_type;

  public:
    Color_T()
      : base_type()
    { }

    Color_T(const base_type& a_other)
      : base_type(a_other)
    { }

    template <typename U>
    explicit Color_T(const core_ds::Tuple<U, k_size>& a_colorByChannels)
      : base_type(a_colorByChannels)
    { }

    template <typename U>
    explicit Color_T(U r)
      : base_type(core_ds::Tuple<U, 1>(r))
    { }

    template <typename U>
    void             SetAs(U r)
    { base_type::SetAs(core_ds::Tuple<U, 1>(r)); }

    using base_type::SetAs;
    using base_type::GetAs;

    using base_type::operator[];
    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator-;
    using base_type::operator-=;

    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator==;
    using base_type::operator!=;

    using base_type::Get;

  public:
    static const this_type COLOR_BLACK;
    static const this_type COLOR_RED;
  };

  // -----------------------------------------------------------------------
  // static variables

  template <typename T>
  const typename Color_T<T, 1>::this_type
    Color_T<T, 1>::COLOR_BLACK = Color_T<T, 1>(0);

  template <typename T>
  const typename Color_T<T, 1>::this_type
    Color_T<T, 1>::COLOR_RED = Color_T<T, 1>(255);

  // -----------------------------------------------------------------------
  // typedefs

  typedef Color_T<u8, 4>                                  Color;
  typedef Color_T<u8, 4>                                  color_rgba;
  typedef Color_T<u8, 3>                                  color_rgb;
  typedef Color_T<u8, 2>                                  color_rg;
  typedef Color_T<u8, 1>                                  color_r;

  typedef Color_T<u8, 1>                                  color_u8_r;
  typedef Color_T<u8, 2>                                  color_u8_rg;
  typedef Color_T<u8, 3>                                  color_u8_rgb;
  typedef Color_T<u8, 4>                                  color_u8_rgba;

  typedef Color_T<u16, 1>                                 color_u16_r;
  typedef Color_T<u16, 2>                                 color_u16_rg;
  typedef Color_T<u16, 3>                                 color_u16_rgb;
  typedef Color_T<u16, 4>                                 color_u16_rgba;

  typedef Color_T<f32, 1>                                 color_f32_r;
  typedef Color_T<f32, 2>                                 color_f32_rg;
  typedef Color_T<f32, 3>                                 color_f32_rgb;
  typedef Color_T<f32, 4>                                 color_f32_rgba;

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u8 TLOC_COMMA 1>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u8 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u8 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u8 TLOC_COMMA 4>);

  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u16 TLOC_COMMA 1>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u16 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u16 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<u16 TLOC_COMMA 4>);

  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<f32 TLOC_COMMA 1>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<f32 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<f32 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Color_TI<f32 TLOC_COMMA 4>);

  // -----------------------------------------------------------------------

  namespace f_color
  {
    template <typename T, tl_size T_Size>
    gfx_t::Color_T<T, T_Size>
      Encode(const math_t::Vector_T<T, T_Size>& a_vec,
      math::Range_T<T> a_minMax)
    {
      TLOC_STATIC_ASSERT_IS_FLOAT(T);

      typedef gfx_t::Color_T<T, T_Size>       color_type;
      typedef math_t::Vector_T<T, T_Size>     vec_type;

      vec_type norm(0 - a_minMax.front());
      vec_type clampedVec = core::Clamp(a_vec, a_minMax.front(), a_minMax.back());

      norm = ( norm + clampedVec ) / a_minMax.difference();

      return color_type(norm);
    }

    // -----------------------------------------------------------------------

    template <typename T, tl_size T_Size>
    math_t::Vector_T<T, T_Size>
      Decode(const gfx_t::Color_T<T, T_Size>& a_color,
      math::Range_T<T> a_range)
    {
      TLOC_STATIC_ASSERT_IS_FLOAT(T);

      typedef gfx_t::Color_T<T, T_Size>       color_type;
      typedef math_t::Vector_T<T, T_Size>     vec_type;

      const auto diff = a_range.difference();
      const auto diffVec = vec_type(0 - a_range.front());

      auto ret = a_color.GetAs<p_color::format::RGBA, vec_type>();
      ret = ( ret * diff ) - diffVec;

      return ret;
    }
  };

};};};

#endif