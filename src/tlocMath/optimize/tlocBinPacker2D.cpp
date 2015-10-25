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
  { return DoProcess<T_PackingAlgorithm>(nullptr); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_PackingAlgorithm, typename T_PackingAlgoParams>
  BinPacker2D::error_type
    BinPacker2D::
    Process(T_PackingAlgoParams a_params)
  { return DoProcess<T_PackingAlgorithm>(a_params); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_PackingAlgorithm>
  T_PackingAlgorithm 
    DoCreatePackingAlgo(Bin::dim_type a_dim, std::nullptr_t)
  { return T_PackingAlgorithm(a_dim); }

  template <typename T_PackingAlgorithm, typename T_PackingAlgoParams>
  T_PackingAlgorithm 
    DoCreatePackingAlgo(Bin::dim_type a_dim, T_PackingAlgoParams a_params)
  { return T_PackingAlgorithm(a_dim, a_params); }

  template <typename T_PackingAlgorithm, typename T_PackingAlgoParams>
  BinPacker2D::error_type
    BinPacker2D::
    DoProcess(T_PackingAlgoParams a_params)
  {
    typedef T_PackingAlgorithm            packing_algo;

    auto tempBin = m_bin;

    auto binDim = tempBin->GetBinDimensions();
    packing_algo pa = DoCreatePackingAlgo<packing_algo>(binDim, a_params);

    auto itr = tempBin->m_cases.begin();
    auto itrEnd = tempBin->m_cases.end();
    while (itr != itrEnd)
    {
      TLOC_ASSERT(itr->GetRectangle().IsValid(), "The case rectangle is invalid");

      case_type packedCase = pa.Insert(*itr);
      if (packedCase.IsValid())
      { 
        tempBin->m_packedCases.push_back(packedCase);
        ++itr;
      }
      else
      { 
        if (tempBin->GetAutoExpand() == false)
        { return TLOC_ERROR(math_err::error_exceeded_size_limit); }

        if (tempBin->GetPowerOfTwo())
        { 
          if (binDim[0] < binDim[1])
          { 
            binDim[0] += itr->GetRectangle().GetDimensions()[0];
            binDim[0] = math::RoundUpPowOfTwo(binDim[0]);
          }
          else
          { 
            binDim[1] += itr->GetRectangle().GetDimensions()[1];
            binDim[1] = math::RoundUpPowOfTwo(binDim[1]);
          }
        }
        else
        {
          const auto rectDim = itr->GetRectangle().GetDimensions();
          binDim = core_ds::Add(binDim, rectDim);
        }

        tempBin->SetBinDimensions(binDim);
        tempBin->m_packedCases.clear();
        pa = packing_algo(binDim);

        itr = m_bin->m_cases.begin();
      }
    }

    m_bin = tempBin;

    return ErrorSuccess;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template BinPacker2D::error_type BinPacker2D::Process<GuillotineBinPack>();
  template BinPacker2D::error_type BinPacker2D::Process
    <GuillotineBinPack, p_guillotine_bin_pack::Params>(p_guillotine_bin_pack::Params);
  template BinPacker2D::error_type BinPacker2D::DoProcess
    <GuillotineBinPack, p_guillotine_bin_pack::Params>(p_guillotine_bin_pack::Params);

};};};

using namespace tloc::math::optimize;

#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(BinPacker2D::rect_type);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Bin);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Bin);