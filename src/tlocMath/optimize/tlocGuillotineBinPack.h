#ifndef _TLOC_MATH_OPTIMIZE_GUILLOTINE_BIN_PACK_H_
#define _TLOC_MATH_OPTIMIZE_GUILLOTINE_BIN_PACK_H_

#include <tlocMath/optimize/tlocBinPackAlgorithms.h>

namespace tloc { namespace math { namespace optimize {

  namespace p_guillotine_bin_pack {

    namespace free_rect_choice {

      struct BestAreaFit          { enum { k_value = 0 }; };
      struct BestShortSideFit     { enum { k_value = 1 }; };
      struct BestLongSideFit      { enum { k_value = 2 }; };
      struct WorstAreaFit         { enum { k_value = 3 }; };
      struct WorstShortSideFit    { enum { k_value = 4 }; };
      struct WorstLongSideFit     { enum { k_value = 5 }; };

    };

    namespace split {

      struct ShorterLeftoverAxis  { enum { k_value = 0 }; };
      struct LongerLeftoverAxis   { enum { k_value = 1 }; };
      struct MinimizeArea         { enum { k_value = 2 }; };
      struct MaximizeArea         { enum { k_value = 3 }; };
      struct ShorterAxis          { enum { k_value = 4 }; };
      struct LongerAxis           { enum { k_value = 5 }; };

    };

  };

  // This algorithm is a port of the packer written (or compiled?) by Jukka 
  // Jylanki

  class GuillotineBinPack
    : public BinPackAlgorithm_I
  {
  public:
    typedef GuillotineBinPack                                 this_type;

  public:
    GuillotineBinPack();

    case_type Insert(case_type a_case) override;
    real_type OccupancyRatio() const override;

    void      MergeFreeList();

  private:
    void      DoSplitFreeRectAlongAxis(const case_type& a_freeCase, 
                                       const case_type& a_placedRect,
                                       bool a_splitHorizontal);

  private:
    tl_int m_freeRectChoice;
    tl_int m_split;
    bool   m_mergeOnInsert;

  public:
    template <typename T_Heuristic>
    this_type& FreeRectChoice()
    {
      using namespace heuristic::guillotine::free_rect_choice;
      type_traits::AssertTypeIsSupported<T_Heuristic,
        BestAreaFit, BestShortSideFit, BestLongSideFit, WorstAreaFit, 
        WorstShortSideFit, WorstLongSideFit>();

      m_freeRectChoice = T_Heuristic::k_value;
      return *this;
    }

    template <typename T_Heuristic>
    this_type& Split()
    {
      using namespace heuristic::guillotine::split;
      type_traits::AssertTypeIsSupported<T_Heuristic,
        ShorterLeftoverAxis, LongerLeftoverAxis, MinimizeArea, MaximizeArea, 
        ShorterAxis, LongerAxis>();

      m_split = T_Heuristic::k_value;
      return *this;
    }

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN_AUTO(MergeOnInsert, m_mergeOnInsert);
  };

};};};

#endif