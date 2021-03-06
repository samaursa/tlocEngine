#ifndef _TLOC_MATH_OPTIMIZE_BIN_PACK_ALGORITHMS_
#define _TLOC_MATH_OPTIMIZE_BIN_PACK_ALGORITHMS_

#include <tlocMath/optimize/tlocBin.h>

namespace tloc { namespace math { namespace optimize {

  class BinPackAlgorithm_I
  {
  public:
    typedef BinPackAlgorithm_I                                  this_type;
    typedef Bin                                                 bin_type;
    typedef bin_type::case_type                                 case_type;
    typedef bin_type::case_cont                                 case_cont;
    typedef case_type::rect_type                                rect_type;
    typedef rect_type::point_type                               dim_type;
    typedef f32                                                 real_type;

  public:
    virtual case_type Insert(case_type a_case) = 0;
    virtual real_type OccupancyRatio() const = 0;

  protected:
    explicit 
    BinPackAlgorithm_I(dim_type a_binDim);
    ~BinPackAlgorithm_I();

  protected:
    case_cont       m_usedCases;
    case_cont       m_freeCases;
    dim_type        m_binDim;

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetBinDimensions, m_binDim);

  };

};};};

#endif