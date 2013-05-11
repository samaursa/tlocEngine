#include "tlocTextureCoords.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  TextureCoords::
    TextureCoords()
    : base_type(k_component_type)
  { }

  TextureCoords::
    TextureCoords(const cont_type& a_coords)
    : base_type(k_component_type)
    , m_coords(a_coords)
  { }

  TextureCoords::size_type
    TextureCoords::
    AddCoord(const vec_type& a_coord)
  {
    m_coords.push_back(a_coord);
    return m_coords.size() - 1;
  }

  void TextureCoords::
    ModifyCoord(const vec_type& a_coord, size_type a_index)
  {
    m_coords[a_index] = a_coord;
  }

  TextureCoords::vec_type
    TextureCoords::
    GetCoord(size_type a_index) const
  {
    return m_coords[a_index];
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureCoords);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(texture_coords_sptr);

};};};