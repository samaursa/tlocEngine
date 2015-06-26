#include "tlocBin.h"

namespace tloc { namespace math { namespace optimize {

  // ///////////////////////////////////////////////////////////////////////
  // Case

  Case::
    Case()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Case::
    Case(rect_type a_rectangle)
    : m_rectangle(a_rectangle)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Case::
    Case(rect_type a_rectangle, user_type a_data)
    : m_rectangle(a_rectangle)
    , m_data(a_data)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetX() const -> value_type
  { return m_rectangle.GetPosition()[0]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetY() const -> value_type
  { return m_rectangle.GetPosition()[1]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetX(value_type a_x) -> this_type& 
  { 
    m_rectangle.SetPosition(core_ds::MakeTuple(a_x, GetY())); 
    return *this; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetY(value_type a_y) -> this_type& 
  { 
    m_rectangle.SetPosition(core_ds::MakeTuple(GetX(), a_y)); 
    return *this; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetWidth() const -> value_type
  { return m_rectangle.GetWidth(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    GetHeight() const -> value_type
  { return m_rectangle.GetHeight(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetWidth(value_type a_x) -> this_type&
  { m_rectangle.SetWidth(a_x); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Case::
    SetHeight(value_type a_y) -> this_type&
  { m_rectangle.SetHeight(a_y); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Case::
    IsValid() const
  { return GetRectangle().IsValid(); }

  // ///////////////////////////////////////////////////////////////////////
  // Bin

  Bin::
    Bin()
    : m_binDim(core_ds::MakeTuple(32, 32))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Bin::
    Bin(dim_type a_dim)
    : m_binDim(a_dim)
    , m_autoExpand(true)
    , m_powerOfTwo(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Bin::
    push_back(const case_type& a_case)
  {
    m_cases.push_back(a_case);
  }

};};};