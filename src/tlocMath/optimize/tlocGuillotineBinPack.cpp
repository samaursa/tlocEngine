#include "tlocGuillotineBinPack.h"

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // GuillotineBinPack

  GuillotineBinPack::
    GuillotineBinPack(rect_type a_bin)
    : base_type(a_bin)
    , m_freeRectChoice(p_guillotine_bin_pack::free_rect_choice::BestAreaFit::k_value) 
    , m_splitMethod(p_guillotine_bin_pack::split::ShorterLeftoverAxis::k_value) 
    , m_mergeOnInsert(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    GuillotineBinPack::
    Insert(case_type a_case) -> case_type
  {
    tl_size freeNodeIndex = 0;
    case_type newCase = DoFindPositionForNewNode(a_case, m_freeRectChoice, freeNodeIndex);

    // could not find enough space
    if (newCase.GetHeight() == 0)
    { return newCase; }

    DoSplitFreeRectByHeuristic(m_freeCases[freeNodeIndex], newCase, m_splitMethod);
    m_freeCases.erase(m_freeCases.begin() + freeNodeIndex);

    if (m_mergeOnInsert) { MergeFreeList(); }

    m_usedCases.push_back(newCase);

    return newCase;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    GuillotineBinPack::
    MergeFreeList()
  {
    for (size_t i = 0; i < m_freeCases.size(); ++i)
    for (size_t j = i + 1; j < m_freeCases.size(); ++j)
    {
      auto rect_i = m_freeCases[i].GetRectangle();
      auto rect_j = m_freeCases[j].GetRectangle();
      
      auto i_coord = rect_i.GetCoord_TopLeft();
      auto j_coord = rect_j.GetCoord_TopLeft();

      if (rect_i.GetWidth() == rect_j.GetWidth() && i_coord[0] == j_coord[0])
      {
        if (i_coord[1] == j_coord[1] + rect_j.GetHeight())
        {
          i_coord[1] -= rect_j.GetHeight();
          rect_i.SetHeight(rect_i.GetHeight() + rect_j.GetHeight());
          m_freeCases[i].SetRectangle(rect_i);
          m_freeCases.erase(m_freeCases.begin() + j);
          --j;
        }
        else if (i_coord[1] + rect_i.GetHeight() == j_coord[1])
        {
          rect_i.SetHeight(rect_i.GetHeight() + rect_j.GetHeight());
          m_freeCases[i].SetRectangle(rect_i);
          m_freeCases.erase(m_freeCases.begin() + j);
          --j;
        }
      }
      else if (rect_i.GetHeight() == rect_j.GetHeight() && i_coord[1] == j_coord[1])
      {
        if (i_coord[0] == j_coord[0] + rect_j.GetWidth())
        {
          i_coord[0] -= rect_j.GetWidth();
          rect_i.SetWidth(rect_i.GetWidth() + rect_j.GetWidth());
          m_freeCases.erase(m_freeCases.begin() + j);
          --j;
        }
        else if (i_coord[0] + rect_i.GetWidth() == j_coord[0])
        {
          rect_i.SetWidth(rect_i.GetWidth() + rect_j.GetWidth());
          m_freeCases.erase(m_freeCases.begin() + j);
          --j;
        }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    GuillotineBinPack::
    OccupancyRatio() const -> real_type
  {
    case_type::value_type usedSurfaceArea = 0;
    for (auto itr = m_usedCases.begin(), itrEnd = m_usedCases.end();
         itr != itrEnd; ++itr)
    { usedSurfaceArea += itr->GetRectangle().GetArea(); }

    return core_utils::CastNumber<real_type>(usedSurfaceArea) / 
            GetBinRectangle().GetArea();
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int
    GuillotineBinPack::
    DoScoreByHeuristic(const case_type& a_newCase, const case_type& a_freeCase, 
                       tl_int a_freeRectChoiceHeuristic) const
  {
    using namespace p_guillotine_bin_pack::free_rect_choice;
    switch(a_freeRectChoiceHeuristic)
    {
    case BestAreaFit::k_value:       return DoScoreBestAreaFit(a_newCase, a_freeCase);
    case BestShortSideFit::k_value:  return DoScoreBestShortSideFit(a_newCase, a_freeCase);
    case BestLongSideFit::k_value:   return DoScoreBestLongSideFit(a_newCase, a_freeCase);
    case WorstAreaFit::k_value:      return DoScoreWorstAreaFit(a_newCase, a_freeCase);
    case WorstShortSideFit::k_value: return DoScoreWorstShortSideFit(a_newCase, a_freeCase);
    case WorstLongSideFit::k_value:  return DoScoreWorstLongSideFit(a_newCase, a_freeCase);
    default: 
      TLOC_ASSERT_FALSE("Invalid heuristic");    
      return NumericLimits_T<tl_int>::max();
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int
    GuillotineBinPack::
    DoScoreBestAreaFit(const case_type& a_case, 
                       const case_type& a_freeCase) const
  {
    return a_freeCase.GetRectangle().GetArea() - a_case.GetRectangle().GetArea();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int
    GuillotineBinPack::
    DoScoreBestShortSideFit(const case_type& a_case, 
                            const case_type& a_freeCase) const
  {
    tl_int leftoverHoriz  = math::Abs(a_freeCase.GetWidth() - a_case.GetWidth());
    tl_int leftoverVert   = math::Abs(a_freeCase.GetHeight() - a_case.GetHeight());
    tl_int leftover = core::tlMin(leftoverHoriz, leftoverVert);
    return leftover;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int
    GuillotineBinPack::
    DoScoreBestLongSideFit(const case_type& a_case, 
                           const case_type& a_freeCase) const
  {
    tl_int leftoverHoriz  = math::Abs(a_freeCase.GetWidth() - a_case.GetWidth());
    tl_int leftoverVert   = math::Abs(a_freeCase.GetHeight() - a_case.GetHeight());
    tl_int leftover = core::tlMax(leftoverHoriz, leftoverVert);
    return leftover;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int 
    GuillotineBinPack::
    DoScoreWorstAreaFit(const case_type& a_case, 
                        const case_type& a_freeCase) const
  { return DoScoreBestAreaFit(a_case, a_freeCase) * -1; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int 
    GuillotineBinPack::
    DoScoreWorstShortSideFit(const case_type& a_case, 
                             const case_type& a_freeCase) const
  { return DoScoreBestShortSideFit(a_case, a_freeCase) * -1; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int 
    GuillotineBinPack::
    DoScoreWorstLongSideFit(const case_type& a_case, 
                            const case_type& a_freeCase) const
  { return DoScoreBestLongSideFit(a_case, a_freeCase) * -1; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    GuillotineBinPack::
    DoFindPositionForNewNode(const case_type& a_newCase, 
                             tl_int a_freeRectChoiceHeuristic, 
                             tl_size& a_nodeIndexOut) const -> case_type
  {
    case_type bestNode;

    tl_int bestScore = NumericLimits_T<tl_int>::max();

    auto freeCaseSize = core_utils::CastNumber<tl_size>(m_freeCases.size());
    for (tl_size i = 0; i < freeCaseSize; ++i)
    {
      if (a_newCase.GetWidth() == m_freeCases[i].GetWidth() && 
          a_newCase.GetHeight() == m_freeCases[i].GetHeight())
      {
        bestNode.SetX(m_freeCases[i].GetX());
        bestNode.SetY(m_freeCases[i].GetY());
        bestNode.SetWidth(a_newCase.GetWidth());
        bestNode.SetHeight(a_newCase.GetHeight());
        bestScore = NumericLimits_T<tl_int>::min();
        a_nodeIndexOut = i;
        break;
      }
      else if (a_newCase.GetHeight() == m_freeCases[i].GetWidth() &&
               a_newCase.GetWidth() == m_freeCases[i].GetHeight())
      {
        bestNode.SetX(m_freeCases[i].GetX());
        bestNode.SetY(m_freeCases[i].GetY());
        bestNode.SetWidth(a_newCase.GetHeight());
        bestNode.SetHeight(a_newCase.GetWidth());
        bestScore = NumericLimits_T<tl_int>::min();
        a_nodeIndexOut = i;
        break;
      }
      else if (a_newCase.GetWidth() <= m_freeCases[i].GetWidth() &&
               a_newCase.GetHeight() <= m_freeCases[i].GetHeight())
      {
        tl_int score = DoScoreByHeuristic(a_newCase, m_freeCases[i], 
                                          a_freeRectChoiceHeuristic);
        if (score < bestScore)
        {
          bestNode.SetX(m_freeCases[i].GetX());
          bestNode.SetY(m_freeCases[i].GetY());
          bestNode.SetWidth(a_newCase.GetWidth());
          bestNode.SetHeight(a_newCase.GetHeight());
          bestScore = score;
          a_nodeIndexOut = i;
        }
      }
      else if (a_newCase.GetHeight() <= m_freeCases[i].GetWidth() &&
               a_newCase.GetWidth() <= m_freeCases[i].GetHeight())
      {
        tl_int score = DoScoreByHeuristic(a_newCase, m_freeCases[i],
                                          a_freeRectChoiceHeuristic);
        if (score < bestScore)
        {
          bestNode.SetX(m_freeCases[i].GetX());
          bestNode.SetY(m_freeCases[i].GetY());
          bestNode.SetWidth(a_newCase.GetHeight());
          bestNode.SetHeight(a_newCase.GetWidth());
          bestScore = score;
          a_nodeIndexOut = i;
        }
      }
    }

    return bestNode;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    GuillotineBinPack::
    DoSplitFreeRectByHeuristic(const case_type& a_freeRect, 
                               const case_type& a_placedRect, 
                               tl_int a_splitMethod)
  {
    using namespace p_guillotine_bin_pack::split;

    const auto w = a_freeRect.GetWidth() - a_placedRect.GetWidth();
    const auto h = a_freeRect.GetHeight() - a_placedRect.GetHeight();

    bool splitHorizontal;
    switch(a_splitMethod)
    {
    case ShorterLeftoverAxis::k_value:
      splitHorizontal = (w <= h);
      break;
    case LongerLeftoverAxis::k_value:
      splitHorizontal = (w > h);
      break;
    case MinimizeArea::k_value:
      splitHorizontal = (a_placedRect.GetWidth() * h > w * a_placedRect.GetHeight());
      break;
    case MaximizeArea::k_value:
      splitHorizontal = (a_placedRect.GetWidth() * h <= w * a_placedRect.GetHeight());
      break;
    case ShorterAxis::k_value:
      splitHorizontal = (a_freeRect.GetWidth() <= a_freeRect.GetHeight());
      break;
    case LongerAxis::k_value:
      splitHorizontal = (a_freeRect.GetWidth() > a_freeRect.GetHeight());
      break;
    default:
      splitHorizontal = true;
      TLOC_ASSERT_FALSE("Invalid split method");
    }

    DoSplitFreeRectAlongAxis(a_freeRect, a_placedRect, splitHorizontal);
  }
 
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    GuillotineBinPack::
    DoSplitFreeRectAlongAxis(const case_type& a_freeCase, 
                             const case_type& a_placedRect, 
                             bool a_splitHorizontal)
  {
    case_type bottom;
    bottom.SetX(a_freeCase.GetX());
    bottom.SetY(a_freeCase.GetY() + a_placedRect.GetHeight());
    bottom.SetHeight(a_freeCase.GetHeight() - a_placedRect.GetHeight());

    case_type right;
    right.SetX(a_freeCase.GetX() + a_placedRect.GetWidth());
    right.SetY(a_freeCase.GetY());
    right.SetWidth(a_freeCase.GetWidth() - a_placedRect.GetWidth());

    if (a_splitHorizontal)
    {
      bottom.SetWidth(a_freeCase.GetWidth());
      right.SetHeight(a_placedRect.GetHeight());
    }
    else
    {
      bottom.SetWidth(a_placedRect.GetWidth());
      right.SetHeight(a_freeCase.GetHeight());
    }

    if (bottom.GetRectangle().IsValid())
    { m_freeCases.push_back(bottom); }
    if (right.GetRectangle().IsValid())
    { m_freeCases.push_back(right); }
  }

};};};