#ifndef _TLOC_MATH_OPTIMIZE_BIN_H_
#define _TLOC_MATH_OPTIMIZE_BIN_H_

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace math { namespace optimize {

  class BinPacker2D;

  class Case
  {
  public:
    typedef Case                                          this_type;
    typedef math_t::Rects_bl                              rect_type;
    typedef rect_type::value_type                         value_type;
    typedef core_t::Any                                   user_type;

  private:
    rect_type   m_rectangle;
    user_type   m_data;

  public:
    Case();
    explicit 
    Case(rect_type a_rectangle);
    Case(rect_type a_rectangle, user_type a_data);

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetRectangle, m_rectangle);
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetData, m_data);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN_AUTO(SetRectangle, m_rectangle);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN_AUTO(SetData, m_data);

    value_type  GetX() const;
    value_type  GetY() const;

    this_type&  SetX(value_type a_x);
    this_type&  SetY(value_type a_y);

    value_type  GetWidth() const;
    value_type  GetHeight() const;

    this_type&  SetWidth(value_type a_x);
    this_type&  SetHeight(value_type a_y);

  };

  class Bin
  {
    friend class BinPacker2D;

  public:
    typedef Bin                                           this_type;
    typedef Case                                          case_type;
    typedef case_type::rect_type                          rect_type;
    typedef rect_type::point_type                         dim_type;

    typedef Case::user_type                               user_type;

    typedef core_conts::Array<case_type>                  case_cont;
    typedef case_cont::iterator                           iterator;
    typedef case_cont::const_iterator                     const_iterator;

    typedef core_err::Error                               error_type;

    typedef core_t::StrongType_T<bool, 0>                 constant_dimension;

  public:
    Bin();
    Bin(dim_type a_startingDimensions);

    void            push_back(const case_type& a_case);

    const_iterator  begin() const;
    const_iterator  end() const;

    TLOC_DECL_AND_DEF_GETTER(dim_type, GetBinDimensions, m_bimDimensions);

  private:
    dim_type            m_bimDimensions;
    case_cont           m_cases;
    case_cont           m_packedCases;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_packed, m_packedCases);
    TLOC_DECL_AND_DEF_CONTAINER_CONST_METHODS(, m_cases);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Bin, bin);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Bin, bin);

};};};

#endif