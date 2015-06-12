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
    typedef f32                                                 real_type;

  public:
    virtual case_type Insert(case_type a_case) = 0;
    virtual real_type OccupancyRatio() const = 0;

  protected:
    BinPackAlgorithm_I();
    ~BinPackAlgorithm_I();

  protected:
    case_cont       m_usedCases;
    case_cont       m_freeCases;

  };

};};};

#endif