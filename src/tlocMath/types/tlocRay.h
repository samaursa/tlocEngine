#ifndef _TLOC_MATH_TYPES_H_
#define _TLOC_MATH_TYPES_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  template <typename T, tl_size T_Size>
  class Ray_T
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);
    TLOC_STATIC_ASSERT(T_Size == 2 || T_Size == 3,
      Ray_only_supports_size_value_of_2_or_3);

  public:
    typedef Ray_T<T, T_Size>        this_type;
    typedef Vector<T, T_Size>       vec_type;

    typedef core::types::StrongType_T<vec_type, 0>   origin;
    typedef core::types::StrongType_T<vec_type, 1>   direction;

  public:
    Ray_T();
    Ray_T(origin a_origin, direction a_direction = direction(vec_type(0)) );
    Ray_T(const this_type& a_other);

    ~Ray_T();

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(vec_type, GetOrigin, m_origin);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(vec_type, GetDirection, m_direction);

  private:
    vec_type m_origin;
    vec_type m_direction;

  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Ray_T<tl_float, 2> Ray2f;
  typedef Ray_T<tl_float, 3> Ray3f;

  typedef Ray_T<f32, 2>     Ray2f32;
  typedef Ray_T<f32, 3>     Ray3f32;

  typedef Ray_T<f64, 2>     Ray2f64;
  typedef Ray_T<f64, 3>     Ray3f64;


};};};

#endif