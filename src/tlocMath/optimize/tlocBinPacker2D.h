#ifndef _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_
#define _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/optimize/tlocBin.h>
#include <tlocMath/optimize/tlocGuillotineBinPack.h>

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // BinPacker2D

  class BinPacker2D
  {
  public:
  public:
    typedef BinPacker2D                                   this_type;

    typedef bin_vptr                                      bin_ptr;
    typedef bin_ptr::value_type                           bin_type;

    typedef bin_type::rect_type                           rect_type;
    typedef bin_type::case_type                           case_type;
    typedef rect_type::dim_type                           dim_type;
    typedef bin_type::case_cont                           case_cont;

    typedef core_err::Error                               error_type;
    typedef f32                                           real_type;

  public:
    BinPacker2D(bin_ptr a_ptr);

    template <typename T_PackingAlgorithm = GuillotineBinPack>
    error_type      Process();

    template <typename T_PackingAlgorithm, typename T_PackingAlgoParams>
    error_type      Process(T_PackingAlgoParams a_params);

  private:
    template <typename T_PackingAlgorithm, typename T_PackingAlgoParams>
    error_type      DoProcess(T_PackingAlgoParams a_params);

  private:
    bin_ptr             m_bin;

  };

};};};

#endif