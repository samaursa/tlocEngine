#include "tlocBinPacker2D.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/data_structures/tlocTuple.h>

#include <tlocMath/error/tlocErrorTypes.h>

#include <3rdParty/Graphics/RectangleBinPack/GuillotineBinPack.h>

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // BinPacker2D

  template <typename T_ComparisonFunctionObject>
  struct CompareBinary
  {
    typedef T_ComparisonFunctionObject          cfo_type;

    template <typename T_RectUserPair>
    bool operator()(const T_RectUserPair& a, 
                    const T_RectUserPair& b)
    { 
      return T_ComparisonFunctionObject()(a.first, b.first);
    }
  };

  template <typename T_ComparisonFunctionObject>
  struct Compare
  {
    typedef Bin::rect_type                      rect_type;
    typedef T_ComparisonFunctionObject          cfo_type;
    
    Compare(const rect_type& a_toCompare, cfo_type a_fo)
      : m_rect(&a_toCompare)
      , m_cfo(a_fo)
    { }

    template <typename T_RectUserPair>
    bool operator()(const T_RectUserPair& a_other)
    { 
      return a_fo(a_other.first);
    }

    const rect_type* m_rect;
    cfo_type         m_cfo;
  };

  template <typename T_ComparisonFunctionObject>
  Compare<T_ComparisonFunctionObject>
    MakeCompare(Bin::rect_type a_toCompare, T_ComparisonFunctionObject a_cfo)
  {
    return Compare<T_ComparisonFunctionObject>(a_toCompare, a_cfo);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::
    BinPacker2D(bin_ptr a_ptr)
    : m_bin(a_ptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_PackingAlgorithm>
  BinPacker2D::error_type
    BinPacker2D::
    Process()
  { return DoProcess<T_PackingAlgorithm>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_PackingAlgorithm>
  BinPacker2D::error_type
    BinPacker2D::
    DoProcess()
  {
    typedef T_PackingAlgorithm            packing_algo;

    packing_algo pa(m_bin->GetBinDimensions());

    for (auto itr = m_bin->m_cases.begin(), itrEnd = m_bin->m_cases.end();
         itr != itrEnd; ++itr)
    {
      case_type packedCase = pa.Insert(*itr);
      if (packedCase.IsValid())
      { m_bin->m_packedCases.push_back(packedCase); }
      else
      { return TLOC_ERROR(math_err::error_exceeded_size_limit); }
    }

    return ErrorSuccess;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template BinPacker2D::error_type BinPacker2D::Process<GuillotineBinPack>();
  template BinPacker2D::error_type BinPacker2D::DoProcess<GuillotineBinPack>();

};};};

using namespace tloc::math::optimize;

#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(BinPacker2D::rect_type);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Bin);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Bin);