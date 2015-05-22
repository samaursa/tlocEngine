#include "tlocBinPacker2D.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/data_structures/tlocTuple.h>

#include <3rdParty/Graphics/RectangleBinPack/GuillotineBinPack.h>

namespace tloc { namespace math { namespace optimize {

  BinPacker2D::dim_type
    BinPacker2D::s_maxDimensions = core_ds::MakeTuple(8192, 8192);

  // ///////////////////////////////////////////////////////////////////////
  // Bin

  Bin::
    Bin()
    : m_bimDimensions(core_ds::MakeTuple(32, 32))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Bin::
    Bin(dim_type a_startingDimension)
    : m_bimDimensions(a_startingDimension)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Bin::
    Add(const rect_user_pair& a_pair)
  {
    m_bin.push_back(a_pair);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Bin::const_iterator 
    Bin::
    begin() const
  { return m_bin.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Bin::const_iterator 
    Bin::
    end() const
  { return m_bin.end(); }

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::error_type
    BinPacker2D::
    Process()
  {
    return Process(this_type::GetMaxDimensions());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::rect_cont
    DoBreakRectangle(BinPacker2D::rect_type a_rectToFit,
                     BinPacker2D::rect_type a_rect)
  {
    // we want the rectangle that we are trying to fit to be at the exact
    // same starting point as the containing rectangle
    a_rect.SetPosition(a_rectToFit.GetPosition());

    typedef BinPacker2D::rect_type            rect_type;
    typedef rect_type::value_type             value_type;

    BinPacker2D::rect_cont freeRects;

    TLOC_ASSERT(a_rect.Fits(a_rectToFit), "a_rect cannot fit a_rectToFit");

    const value_type  rectWidth  = a_rect.GetWidth();
    const value_type  rectHeight = a_rect.GetHeight();

    const value_type  rtfWidth  = a_rectToFit.GetWidth();
    const value_type  rtfHeight = a_rectToFit.GetHeight();

    // after fitting, a maximum of 2 rectangles can be extracted from the 
    // containing rectangle (F = rect to fit, r1 and r2 are free rectangles
    /*

    ---------------           ---------------
    | r1 |        |           | r1          |
    |____|        |   OR      |_____________| 
    |    |   r2   |           |    |   r2   |
    | F  |        |           | F  |        |
    ---------------           ---------------

    */
    rect_type r1, r2;

    // to decide which rectangle we favor to be bigger, we look at the fitting
    // rectangle width and height

    bool rtfWidthGreater = rtfWidth > rtfHeight;

    {// top-left free rect (if possible)
      const rect_type::value_type height = rectHeight - rtfHeight;
      const rect_type::value_type width = rtfWidthGreater ? rectWidth : rtfWidth;
      const rect_type::point_type pos =
        core_ds::Add(a_rect.GetPosition(), a_rectToFit.GetCoord_TopLeft());

      r1 = rect_type(rect_type::width(width), rect_type::height(height),
                     rect_type::position(pos));
    }

    { // right free rect (if possible)
      rect_type::value_type height = rtfWidthGreater ? rtfHeight : rectHeight; 
      rect_type::value_type width = rectWidth - rtfWidth;
      rect_type::point_type pos = 
        core_ds::Add(a_rect.GetPosition(), a_rectToFit.GetCoord_BottomRight());
                                              
      r2 = rect_type(rect_type::width(width), rect_type::height(height),
                     rect_type::position(pos));
    }

    if (r1.IsValid()) { freeRects.push_back(r1); }
    if (r2.IsValid()) { freeRects.push_back(r2); }

    return freeRects;
  }

  BinPacker2D::error_type
    BinPacker2D::
    Process(dim_type a_maxDimensions)
  {
    TLOC_UNUSED(a_maxDimensions);

    rect_user_cont sortedPairs = m_packedPairs;

    using namespace math_t::algos::rectangle::compare;

    core::sort(sortedPairs.begin(), sortedPairs.end(),
      CompareBinary<WidthBinary<Less> >(), core::sort_insertionsort());

    rect_user_cont::iterator itr;
    rect_user_cont::iterator itrEnd;

    rect_type::value_type totalWidth = 0;
    for (itr = sortedPairs.begin(), itrEnd = sortedPairs.end(); 
         itr != itrEnd; ++itr)
    { totalWidth += itr->first.GetWidth(); }

    rect_type::value_type totalHeight = 0;
    for (itr = sortedPairs.begin(), itrEnd = sortedPairs.end(); 
         itr != itrEnd; ++itr)
    { totalHeight += itr->first.GetHeight(); }

    const dim_type startingDim = core_ds::MakeTuple(totalWidth, totalHeight);

    m_freeRects.push_back(rect_type(rect_type::width(startingDim[0]), 
                                    rect_type::height(startingDim[1])) );

    for (itr = sortedPairs.begin(), itrEnd = sortedPairs.end();
         itr != itrEnd; ++itr)
    {
      rect_cont::iterator freeRectItr     = m_freeRects.begin();
      rect_cont::iterator freeRectItrEnd  = m_freeRects.end();

      bool fitFound = false;
      for (; freeRectItr != freeRectItrEnd; ++freeRectItr)
      {
        rect_type freeRect = *freeRectItr;
        if (freeRect.Fits(itr->first))
        {
          rect_cont freeRects = DoBreakRectangle(itr->first, freeRect);
          m_freeRects.erase(freeRectItr);
          fitFound = true;
          break;
        }
      }

      if (fitFound == false)
      {
      }
    }

    return ErrorSuccess;
  }

};};};

using namespace tloc::math::optimize;

#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Bin::rect_user_pair);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(BinPacker2D::rect_type);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Bin);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Bin);