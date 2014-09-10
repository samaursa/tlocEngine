#ifndef _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_
#define _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace math { namespace optimize {

  class BinPacker2D;

  class Bin
  {
    friend class BinPacker2D;

  public:
    typedef math_t::Rects_bl                              rect_type;
    typedef rect_type::point_type                         dim_type;

    typedef core_t::Any                                   user_type;
    typedef core::Pair<rect_type, user_type>              rect_user_pair;

    typedef core_conts::Array<rect_user_pair>             rect_user_cont;
    typedef rect_user_cont::iterator                      iterator;
    typedef rect_user_cont::const_iterator                const_iterator;

    typedef core_err::Error                               error_type;

    typedef core_t::StrongType_T<bool, 0>                 constant_dimension;

  public:
    Bin();
    Bin(dim_type a_startingDimensions);

    void            Add(const rect_user_pair& a_pair);

    const_iterator  begin() const;
    const_iterator  end() const;

    TLOC_DECL_AND_DEF_GETTER(dim_type, GetBinDimensions, m_bimDimensions);

  private:
    dim_type            m_bimDimensions;
    rect_user_cont      m_bin;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Bin, bin);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Bin, bin);

  // ///////////////////////////////////////////////////////////////////////
  // BinPacker2D

  class BinPacker2D
  {
  public:
    typedef BinPacker2D                                   this_type;

    typedef bin_vptr                                      bin_ptr;
    typedef bin_ptr::value_type                           bin_type;

    typedef bin_type::rect_type                           rect_type;
    typedef rect_type::dim_type                           dim_type;
    typedef bin_type::rect_user_cont                      rect_user_cont;

    typedef core_conts::Array<rect_type>                  rect_cont;
    typedef core_err::Error                               error_type;

  public:
    BinPacker2D(bin_ptr a_ptr);

    error_type      Process();
    error_type      Process(dim_type a_maxDimensions);

    TLOC_DECL_AND_DEF_GETTER(dim_type, GetPackedBinDimensions, 
                             m_packedBinDimensions);

    static TLOC_DECL_AND_DEF_GETTER_NON_CONST( dim_type, 
                                               GetMaxDimensions, 
                                               s_maxDimensions );
  private:
    error_type      DoProcess(dim_type a_maxDimensions = s_maxDimensions);

  private:
    dim_type            m_packedBinDimensions;
    bin_ptr             m_bin;

    rect_user_cont      m_packedPairs;
    rect_user_cont      m_leftOverPair;
    rect_cont           m_freeRects;

    static dim_type     s_maxDimensions;

  };

};};};

#endif