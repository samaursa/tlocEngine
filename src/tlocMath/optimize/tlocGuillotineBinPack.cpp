#include "tlocGuillotineBinPack.h"

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // GuillotineBinPack

  GuillotineBinPack::
    GuillotineBinPack()
    : m_freeRectChoice(p_guillotine_bin_pack::free_rect_choice::BestAreaFit::k_value) 
    , m_split(p_guillotine_bin_pack::split::ShorterLeftoverAxis::k_value) 
    , m_mergeOnInsert(false)
  { }

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