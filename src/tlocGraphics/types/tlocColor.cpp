#include "tlocColor.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/data_structures/tlocTuple.inl.h>

#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

namespace tloc { namespace graphics { namespace types {

  namespace
  {
    //------------------------------------------------------------------------
    // Converting color to a packed integer. Assuming a_colArray is an array
    // of four bytes in the order RGBA

    typedef u32               int_color_type;

    typedef type_true         byte_type_true;
    typedef type_false        real_type_true;


    using namespace p_color::channel;
    using core_utils::CastNumber;

    namespace detail
    {
      tl_size bitShift[] = {24, 16, 8, 0};

      template <typename T_Real, typename T_ColorValueType>
      T_Real
        DoNormalizeColorValue(T_ColorValueType a_color, byte_type_true)
      {
        TLOC_STATIC_ASSERT
          (( Loki::IsSameType<T_ColorValueType, u8>::value ||
             Loki::IsSameType<T_ColorValueType, u16>::value ), Unsupported_color_type);

        using namespace core::utils;

        static T_Real oneDivMax
          = 1.0f / static_cast<T_Real>(NumericLimits_T<T_ColorValueType>::max());

        return static_cast<T_Real>(a_color) * oneDivMax;
      }

      template <typename T_Real>
      T_Real
        DoNormalizeColorValue(T_Real a_color, real_type_true)
      { return a_color; }

      template <typename T_Real, typename T_ColorValueType>
      T_Real DoNormalizeColor(T_ColorValueType a_color)
      {
        typedef typename Loki::Select
          <
            Loki::TypeTraits<T_ColorValueType>::isFloat,
            real_type_true, byte_type_true
          >::Result                                           selected_type;

        return DoNormalizeColorValue<T_Real>(a_color, selected_type());
      }

      template <typename T_RetVal, typename T_ColorValueType>
      T_RetVal
        DoNormalizeColorAndConvert(T_ColorValueType a_color)
      {
        f32 retValReal = DoNormalizeColor<f32>(a_color);

        return static_cast<T_RetVal>(retValReal * NumericLimits_T<T_RetVal>::max());
      }

      template <typename T_ColorValue>
      u8
        DoGetAsU8(T_ColorValue a_col)
      {
        f32 norm = DoNormalizeColor<f32>(a_col);
        return CastNumber<u8>(norm * NumericLimits_T<u8>::max());
      }

      u8
        DoGetAsU8(f32 a_col)
      {
        return CastNumber<u8>(a_col * NumericLimits_T<u8>::max());
      }

      template <typename T_ContainerType>
      int_color_type
        DoGetAs(const T_ContainerType& a_colArray, p_color::format::RGBA)
      {
        int_color_type  retVal = 0;

        // put as many colors are you can in the int - the rest will be 0
        // NOTE: We convert the color values to u8 because it may be u8, u16
        //       or f32
        switch(a_colArray.size())
        {
        case 1:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          break;
        case 2:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          break;
        case 3:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[b];
          break;
        case 4:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[b];
          retVal |= DoGetAsU8(a_colArray[a]) << bitShift[a];
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }

        return retVal;
      }

      template <typename T_ContainerType>
      int_color_type
        DoGetAs(const T_ContainerType& a_colArray, p_color::format::ABGR)
      {
        int_color_type  retVal = 0;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          break;
        case 2:
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[g];
          break;
        case 3:
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[b];
          break;
        case 4:
          retVal |= DoGetAsU8(a_colArray[a]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[b];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[a];
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }

        return retVal;
      }

      template <typename T_ContainerType>
      int_color_type
        DoGetAs(const T_ContainerType& a_colArray, p_color::format::ARGB)
      {
        int_color_type  retVal = 0;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          break;
        case 2:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          break;
        case 3:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[b];
          break;
        case 4:
          retVal |= DoGetAsU8(a_colArray[a]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[b];
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[a];
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }

        return retVal;
      }

      template <typename T_ContainerType>
      int_color_type
        DoGetAs(const T_ContainerType& a_colArray, p_color::format::BGRA)
      {
        int_color_type  retVal = 0;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[r];
          break;
        case 2:
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[g];
          break;
        case 3:
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[b];
          break;
        case 4:
          retVal |= DoGetAsU8(a_colArray[b]) << bitShift[r];
          retVal |= DoGetAsU8(a_colArray[g]) << bitShift[g];
          retVal |= DoGetAsU8(a_colArray[r]) << bitShift[b];
          retVal |= DoGetAsU8(a_colArray[a]) << bitShift[a];
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }

        return retVal;
      }

      template <typename T_ContainerType, typename T_VectorType>
      void
        DoGetAs(const T_ContainerType& a_colArray, T_VectorType& a_vecOut,
                p_color::format::RGBA)
      {
        typedef typename T_VectorType::value_type value_type;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 2:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          break;
        case 3:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[b]);
          break;
        case 4:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[b]);
          a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[a]);
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }
      }

      template <typename T_ContainerType, typename T_VectorType>
      void
        DoGetAs(const T_ContainerType& a_colArray,
                      T_VectorType& a_vecOut, p_color::format::ABGR)
      {
        typedef typename T_VectorType::value_type value_type;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 2:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          break;
        case 3:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[b]);
          break;
        case 4:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[a]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[b]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }
      }

      template <typename T_ContainerType, typename T_VectorType>
      void
        DoGetAs(const T_ContainerType& a_colArray,
                      T_VectorType& a_vecOut, p_color::format::ARGB)
      {
        typedef typename T_VectorType::value_type value_type;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 2:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          break;
        case 3:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[b]);
          break;
        case 4:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[a]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[b]);
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }
      }

      template <typename T_ContainerType, typename T_VectorType>
      void
        DoGetAs(const T_ContainerType& a_colArray,
                      T_VectorType& a_vecOut, p_color::format::BGRA)
      {
        typedef typename T_VectorType::value_type value_type;

        // put as many colors are you can in the int - the rest will be 0
        switch(a_colArray.size())
        {
        case 1:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 2:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 3:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[b]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[r]);
          break;
        case 4:
          a_vecOut[0] = DoNormalizeColor<value_type>(a_colArray[b]);
          a_vecOut[1] = DoNormalizeColor<value_type>(a_colArray[g]);
          a_vecOut[2] = DoNormalizeColor<value_type>(a_colArray[r]);
          a_vecOut[3] = DoNormalizeColor<value_type>(a_colArray[a]);
          break;
        default:
          TLOC_ASSERT_FALSE("Logic error in tlocColor.cpp");
        }
      }

      // integer to integer conversion
      template <typename T_Integer, tl_int T_Size, typename T_ColorType>
      void
        DoSetAs(core_ds::Tuple<T_Integer, T_Size> a_in,
                core_ds::Tuple<T_ColorType, T_Size> & a_out, byte_type_true, byte_type_true)
      {
        typedef typename core_ds::Tuple<T_ColorType, T_Size>::value_type     value_type;

        for (tl_int i = 0; i < T_Size; ++i)
        { a_out[i] = core::utils::CastNumber<value_type>(a_in[i]); }
      }

      // float to integer conversion
      template <typename T_Real, tl_int T_Size, typename T_ColorType>
      void
        DoSetAs(core_ds::Tuple<T_Real, T_Size> a_in,
                core_ds::Tuple<T_ColorType, T_Size>& a_out, real_type_true, byte_type_true)
      {
        typedef T_Real                                                    real_type;
        typedef typename core_ds::Tuple<T_ColorType, T_Size>::value_type  value_type;

        core_ds::Tuple<real_type, T_Size> clamped;
        for (tl_int i = 0; i < T_Size; ++i)
        { clamped[i] = core::Clamp<real_type>(a_in[i], 0.0f, 1.0f); }

        for (tl_int i = 0; i < T_Size; ++i)
        {
          a_out[i] = static_cast<value_type>
            (NumericLimits_T<value_type>::max() * clamped[i]);
        }
      }

      // float to float, no conversion
      template <typename T_Real, tl_int T_Size, typename T_ColorType>
      void
        DoSetAs(core_ds::Tuple<T_Real, T_Size> a_in,
                core_ds::Tuple<T_ColorType, T_Size> & a_out, real_type_true, real_type_true)
      {
        typedef typename core_ds::Tuple<T_ColorType, T_Size>::value_type     value_type;

        for (tl_int i = 0; i < T_Size; ++i)
        { a_out[i] = core::utils::CastNumber<value_type>(a_in[i]); }
      }

      // u8 to float conversion
      template <typename T_Integer, tl_int T_Size, typename T_ColorType>
      void
        DoSetAs(core_ds::Tuple<T_Integer, T_Size> a_in,
                core_ds::Tuple<T_ColorType, T_Size> & a_out, byte_type_true, real_type_true)
      {
        typedef typename core_ds::Tuple<T_ColorType, T_Size>::value_type     value_type;

        const T_Integer min = 0;
        const T_Integer max = NumericLimits_T<u8>::max();

        for (tl_int i = 0; i < T_Size; ++i)
        {
          T_Integer inValClamped = core::Clamp(a_in[i], min, max);
          u8 inVal = core_utils::CastNumber<u8>(inValClamped);
          a_out[i] = CastNumber<value_type>(inVal) / NumericLimits_T<u8>::max();
        }
      }
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Color_TI

#define TLOC_COLOR_TEMPS    typename T, tl_int T_Size
#define TLOC_COLOR_PARAMS   T, T_Size
#define TLOC_COLOR_TYPE     typename Color_TI<TLOC_COLOR_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  Color_TI<TLOC_COLOR_PARAMS>::
    Color_TI()
    : m_color(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::value_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator[](tl_int a_index)
  {
    return m_color[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  const TLOC_COLOR_TYPE::value_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator[](tl_int a_index) const
  {
    return m_color[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type
    Color_TI<TLOC_COLOR_PARAMS>::
    operator +(const this_type &a_other) const
  {
    this_type temp(*this);

    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { temp[i] += a_other[i]; }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator +=(const this_type &a_other)
  {
    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { m_color[i] += a_other[i]; }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type
    Color_TI<TLOC_COLOR_PARAMS>::
    operator *(const this_type &a_other) const
  {
    this_type temp(*this);

    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { temp[i] *= a_other[i]; }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator *=(const this_type &a_other)
  {
    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { m_color[i] *= a_other[i]; }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type
    Color_TI<TLOC_COLOR_PARAMS>::
    operator -(const this_type &a_other) const
  {
    this_type temp(*this);

    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { temp[i] -= a_other[i]; }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator -=(const this_type &a_other)
  {
    for (tl_int i =0; i < core_utils::CastNumber<tl_int>(m_color.size()); ++i)
    { m_color[i] -= a_other[i]; }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type
    Color_TI<TLOC_COLOR_PARAMS>::
    operator * (real_type a_other) const
  {
    core_ds::Tuple<real_type, k_size>  col;
    GetAs<p_color::format::RGBA>(col);

    col = core_ds::Multiply(a_other, col);

    this_type newCol(col);
    return newCol;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator *=(real_type a_other)
  {
    this_type temp = *this * a_other;

    core::swap(temp, *this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type
    Color_TI<TLOC_COLOR_PARAMS>::
    operator / (real_type a_other) const
  {
    core_ds::Tuple<real_type, k_size>  col;
    GetAs<p_color::format::RGBA>(col);

    col = core_ds::Divide(a_other, col);

    this_type newCol(col);
    return newCol;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  TLOC_COLOR_TYPE::this_type&
    Color_TI<TLOC_COLOR_PARAMS>::
    operator /=(real_type a_other)
  {
    this_type temp = *this / a_other;

    core::swap(temp, *this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  bool
    Color_TI<TLOC_COLOR_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return ( m_color[0] == a_other[0] &&
             m_color[1] == a_other[1] &&
             m_color[2] == a_other[2] &&
             m_color[3] == a_other[3] );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  bool
    Color_TI<TLOC_COLOR_PARAMS>::
    operator !=(const this_type& a_other) const
  {
    return !operator==(a_other);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  template <typename T_ColorFormat>
  TLOC_COLOR_TYPE::int_type
    Color_TI<TLOC_COLOR_PARAMS>::
    DoGetAs() const
  {
    return detail::DoGetAs(m_color, T_ColorFormat());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  template <typename T_ColorFormat, typename T_VectorType>
  void
    Color_TI<TLOC_COLOR_PARAMS>::
    DoGetAs(T_VectorType& a_vec) const
  {
    detail::DoGetAs(m_color, a_vec, T_ColorFormat());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_COLOR_TEMPS>
  template <typename U>
  void
    Color_TI<TLOC_COLOR_PARAMS>::
    DoSetAs(const core_ds::Tuple<U, k_size>& a_colorByChannels)
  {
    typedef typename Loki::Select
      <
        Loki::TypeTraits<U>::isFloat,
        real_type_true, byte_type_true
      >::Result                                           selected_type;

    typedef typename Loki::Select
      <
        Loki::TypeTraits<value_type>::isFloat,
        real_type_true, byte_type_true
      >::Result                                           selected_value_type;

    detail::DoSetAs<U, k_size, value_type>
      (a_colorByChannels, m_color, selected_type(), selected_value_type() );
  }

  //------------------------------------------------------------------------
  // Explicit initialization

  using namespace tloc::math::types;
  using namespace p_color::format;

#define TLOC_INSTANTIATE_COLOR_GET_AS(_type_, _size_, _colorFormat_, _vecType_)\
  template void\
    Color_TI<_type_, _size_>::DoGetAs<_colorFormat_, _vecType_>(_vecType_&) const

#define TLOC_INSTANTIATE_COLOR_GET_AS_ALL_FORMATS(_type_, _size_, _vecType_)\
  TLOC_INSTANTIATE_COLOR_GET_AS(_type_, _size_, RGBA, _vecType_);\
  TLOC_INSTANTIATE_COLOR_GET_AS(_type_, _size_, ABGR, _vecType_);\
  TLOC_INSTANTIATE_COLOR_GET_AS(_type_, _size_, ARGB, _vecType_);\
  TLOC_INSTANTIATE_COLOR_GET_AS(_type_, _size_, BGRA, _vecType_)

#define TLOC_INSTANTIATE_COLOR_GET_AS_INT(_type_, _size_, _colorFormat_)\
  template Color_TI<_type_, _size_>::int_type  \
    Color_TI<_type_, _size_>::DoGetAs<_colorFormat_>() const

#define TLOC_INSTANTIATE_COLOR_GET_AS_INT_ALL_FORMATS(_type_, _size_)\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT(_type_, _size_, p_color::format::RGBA);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT(_type_, _size_, p_color::format::ABGR);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT(_type_, _size_, p_color::format::ARGB);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT(_type_, _size_, p_color::format::BGRA);\

#define TLOC_INSTANTIATE_COLOR_SET_AS(_colorType_, _size_)\
  template void _colorType_::DoSetAs(const core_ds::Tuple<u8, _size_>&);\
  template void _colorType_::DoSetAs(const core_ds::Tuple<s32, _size_>&);\
  template void _colorType_::DoSetAs(const core_ds::Tuple<s64, _size_>&);\
  template void _colorType_::DoSetAs(const core_ds::Tuple<f32, _size_>&);\
  template void _colorType_::DoSetAs(const core_ds::Tuple<f64, _size_>&)

#define TLOC_INSTANTIATE_COLOR_ALL_TYPES(_size_, _vecType_)\
  TLOC_INSTANTIATE_COLOR_GET_AS_ALL_FORMATS(u8, _size_, _vecType_);\
  TLOC_INSTANTIATE_COLOR_GET_AS_ALL_FORMATS(u16, _size_, _vecType_);\
  TLOC_INSTANTIATE_COLOR_GET_AS_ALL_FORMATS(f32, _size_, _vecType_)
  
  
#define TLOC_INSTANTIATE_COLOR_ALL_SIZE(_type_)\
  template class Color_TI<_type_, 1>;\
  template class Color_TI<_type_, 2>;\
  template class Color_TI<_type_, 3>;\
  template class Color_TI<_type_, 4>;\
  TLOC_INSTANTIATE_COLOR_SET_AS(Color_TI<_type_ TLOC_COMMA 1>, 1);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT_ALL_FORMATS(_type_, 1);\
  \
  TLOC_INSTANTIATE_COLOR_SET_AS(Color_TI<_type_ TLOC_COMMA 2>, 2);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT_ALL_FORMATS(_type_, 2);\
  \
  TLOC_INSTANTIATE_COLOR_SET_AS(Color_TI<_type_ TLOC_COMMA 3>, 3);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT_ALL_FORMATS(_type_, 3);\
  \
  TLOC_INSTANTIATE_COLOR_SET_AS(Color_TI<_type_ TLOC_COMMA 4>, 4);\
  TLOC_INSTANTIATE_COLOR_GET_AS_INT_ALL_FORMATS(_type_, 4)
  
  //
  
  TLOC_INSTANTIATE_COLOR_ALL_SIZE(u8);
  TLOC_INSTANTIATE_COLOR_ALL_SIZE(u16);
  TLOC_INSTANTIATE_COLOR_ALL_SIZE(f32);

  TLOC_INSTANTIATE_COLOR_ALL_TYPES(4, Vec4f32);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(3, Vec3f32);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(2, Vec2f32);

  TLOC_INSTANTIATE_COLOR_ALL_TYPES(4, Vec4f64);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(3, Vec3f64);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(2, Vec2f64);

  using namespace core_ds;
  
  typedef Tuple<f32, 1>   Tuple1f32;

  TLOC_INSTANTIATE_COLOR_ALL_TYPES(4, Tuple4f32);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(3, Tuple3f32);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(2, Tuple2f32);
  TLOC_INSTANTIATE_COLOR_ALL_TYPES(1, Tuple1f32);

};};};