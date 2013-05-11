#include "tlocTextureCoords.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  TextureCoords::
    TextureCoords()
    : base_type(k_component_type)
  { }

  TextureCoords::
    TextureCoords(const cont_set_type& a_coords)
    : base_type(k_component_type)
    , m_coordSets(a_coords)
  { }

  TextureCoords::size_type
    TextureCoords::
    AddCoord(const vec_type& a_coord, set_index a_setIndex)
  {
    m_coordSets[a_setIndex].push_back(a_coord);
    return m_coordSets.size() - 1;
  }

  void TextureCoords::
    ModifyCoord(const vec_type& a_coord, size_type a_index,
                set_index a_setIndex)
  {
    m_coordSets[a_setIndex][a_index] = a_coord;
  }

  TextureCoords::vec_type
    TextureCoords::
    GetCoord(size_type a_index, set_index a_setIndex) const
  {
    return m_coordSets[a_setIndex][a_index];
  }

  void TextureCoords::
    DoResizeSetToAccomodate(set_index a_index)
  {
    m_coordSets.resize(a_index + 1);
  }

  const TextureCoords::cont_type&
    TextureCoords::
    GetCoords(set_index a_setIndex) const
  {
    return m_coordSets[a_setIndex];
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureCoords);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(texture_coords_sptr);

};};};