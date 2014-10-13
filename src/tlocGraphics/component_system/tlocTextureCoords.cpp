#include "tlocTextureCoords.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  TextureCoords::
    TextureCoords()
    : base_type(k_component_type, "TextureCoords")
    , m_currentSet(0)
  { }

  TextureCoords::
    TextureCoords(const this_type& a_other)
    : base_type(a_other)
    , m_coordSets(a_other.m_coordSets)
    , m_currentSet(a_other.m_currentSet)
  { }

  TextureCoords::
    TextureCoords(const cont_set_type& a_coords)
    : base_type(k_component_type, "TextureCoords")
    , m_coordSets(a_coords)
    , m_currentSet(0)
  { }

  TextureCoords::this_type&
    TextureCoords::
    operator=(this_type a_other)
  {
    swap(a_other);
    base_type::SetUpdateRequired(true);
    return *this;
  }

  void
    TextureCoords::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_coordSets, a_other.m_coordSets);
    swap(m_currentSet, a_other.m_currentSet);
  }

  TextureCoords::size_type
    TextureCoords::
    AddCoord(const vec_type& a_coord, set_index a_setIndex)
  {
    base_type::SetUpdateRequired(true);

    DoResizeSetToAccomodate(a_setIndex);
    m_coordSets[a_setIndex]->push_back(a_coord);
    return m_coordSets.size() - 1;
  }

  void TextureCoords::
    ModifyCoord(const vec_type& a_coord, size_type a_index,
                set_index a_setIndex)
  {
    base_type::SetUpdateRequired(true);

    DoResizeSetToAccomodate(a_setIndex);
    (*m_coordSets[a_setIndex])[a_index] = a_coord;
  }

  void TextureCoords::
    ModifyCoords(const cont_type& a_coords,
                 set_index a_setIndex)
  {
    base_type::SetUpdateRequired(true);

    DoResizeSetToAccomodate(a_setIndex);
    (*m_coordSets[a_setIndex]) = a_coords;
  }

  void TextureCoords::
    RemoveCoord(size_type a_index, set_index a_setIndex)
  {
    base_type::SetUpdateRequired(true);

    cont_type::iterator itr = m_coordSets[a_setIndex]->begin() + a_index;
    m_coordSets[a_setIndex]->erase(itr);
  }

  void TextureCoords::
    ClearCoords(set_index a_setIndex)
  {
    base_type::SetUpdateRequired(true);
    m_coordSets[a_setIndex]->clear();
  }

  TextureCoords::vec_type
    TextureCoords::
    GetCoord(size_type a_index, set_index a_setIndex) const
  {
    return (*m_coordSets[a_setIndex])[a_index];
  }

  void TextureCoords::
    DoResizeSetToAccomodate(set_index a_index)
  {
    m_coordSets.resize(a_index + 1);
  }

  TextureCoords::cont_type_ptr
    TextureCoords::
    GetCoords(set_index a_setIndex)
  {
    return m_coordSets[a_setIndex].get();
  }

  TextureCoords::const_cont_type_ptr
    TextureCoords::
    GetCoords(set_index a_setIndex) const
  {
    return m_coordSets[a_setIndex].get();
  }

};};};


//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureCoords);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(TextureCoords);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(TextureCoords::cont_type);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(TextureCoords::cont_type);