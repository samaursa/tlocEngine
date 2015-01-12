#pragma once

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace math {

  template <typename T_VecType>
  class Bounds_T
  {
  public:
    typedef T_VecType                             vec_type;
    typedef Bounds_T<vec_type>                    this_type;
    typedef core_conts::Array<vec_type>           vec_cont;

  public:
    Bounds_T(const vec_type& a_allPoints);

    TLOC_DECL_AND_DEF_GETTER(vec_type, GetMax, m_max);
    TLOC_DECL_AND_DEF_GETTER(vec_type, GetMin, m_min);
    
  private:
    vec_type m_max;
    vec_type m_min;
  };

};};