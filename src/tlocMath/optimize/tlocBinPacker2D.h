#ifndef _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_
#define _TLOC_MATH_OPTIMIZE_BIN_PACKER_2D_H_

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/optimize/tlocBin.h>

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // BinPacker2D

  namespace p_bin_packer_2d {

    namespace heuristic {

      namespace guillotine {

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
    };

    namespace algo {

      class Guillotine     
      { 
      public:
        typedef Guillotine                    this_type;

      public:
        Guillotine() 
        : m_freeRectChoice(heuristic::guillotine::free_rect_choice::BestAreaFit::k_value)
        , m_split(heuristic::guillotine::split::ShorterLeftoverAxis::k_value)
        { }

        template <typename T_Heuristic>
        this_type& FreeRectChoice()
        {
          using namespace heuristic::guillotine::free_rect_choice;
          type_traits::AssertTypeIsSupported<T_Heuristic,
            BestAreaFit, BestShortSideFit, BestLongSideFit, WorstAreaFit, 
            WorstShortSideFit, WorstLongSideFit>();

          m_freeRectChoice = T_Heuristic::k_value;
        }

        template <typename T_Heuristic>
        this_type& Split()
        {
          using namespace heuristic::guillotine::split;
          type_traits::AssertTypeIsSupported<T_Heuristic,
            ShorterLeftoverAxis, LongerLeftoverAxis, MinimizeArea, MaximizeArea, 
            ShorterAxis, LongerAxis>();

          m_split = T_Heuristic::k_value;
        }

      private:
        tl_int m_freeRectChoice;
        tl_int m_split;

      public:
        TLOC_DECL_AND_DEF_GETTER_AUTO(GetFreeRectChoice, m_freeRectChoice);
        TLOC_DECL_AND_DEF_GETTER_AUTO(GetSplit, m_split);
      };

      class MaxRectangles  
      { 
      };

      class Shelf          
      { 
      };

      class Skyline        
      { 
      };

    };

  };

  class BinPacker2D
  {
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

    template <typename T_PackingAlgorithm>
    error_type      Process(T_PackingAlgorithm a_algo = 
                            p_bin_packer_2d::algo::Guillotine());

    template <typename T_PackingAlgorithm>
    error_type      Process(dim_type a_maxDimensions, 
                            T_PackingAlgorithm a_algo = 
                            p_bin_packer_2d::algo::Guillotine());

  private:
    error_type      DoProcess(dim_type a_maxDimensions = s_maxDimensions);

  private:
    dim_type            m_packedBinDimensions;
    bin_ptr             m_bin;

    static dim_type     s_maxDimensions;

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetPackedBinDimensions, m_packedBinDimensions);
    static TLOC_DECL_AND_DEF_GETTER_NON_CONST_AUTO(GetMaxDimensions, s_maxDimensions);

  };

};};};

#endif