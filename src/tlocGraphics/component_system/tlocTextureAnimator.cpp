#include "tlocTextureAnimator.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  TextureAnimator::
    TextureAnimator()
    : base_type(k_component_type)
    , m_currentSet(0)
    , m_currentFrame(0)
    , m_fps(24)
    , m_loop(true)
    , m_startTime(0)
  { }

  TextureAnimator::
    TextureAnimator(const cont_set_type& a_coords)
    : base_type(k_component_type)
    , m_coordSets(a_coords)
    , m_currentSet(0)
    , m_currentFrame(0)
    , m_fps(24)
    , m_loop(true)
    , m_startTime(0)
  { }

  TextureAnimator::size_type
    TextureAnimator::
    AddSpriteCoord(const vec_type& a_coord, set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    m_coordSets[a_setIndex]->push_back(a_coord);
    return m_coordSets.size() - 1;
  }

  void TextureAnimator::
    ModifySpriteCoord(const vec_type& a_coord, size_type a_index,
                set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_coordSets[a_setIndex])[a_index] = a_coord;
  }

  void TextureAnimator::
    ModifySpriteCoords(const cont_type& a_coords,
                 set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_coordSets[a_setIndex]) = a_coords;
  }

  void TextureAnimator::
    RemoveSpriteCoord(size_type a_index, set_index a_setIndex)
  {
    cont_type::iterator itr = m_coordSets[a_setIndex]->begin() + a_index;
    m_coordSets[a_setIndex]->erase(itr);
  }

  void TextureAnimator::
    ClearSpriteCoords(set_index a_setIndex)
  {
    m_coordSets[a_setIndex]->clear();
  }

  TextureAnimator::vec_type
    TextureAnimator::
    GetSpriteCoord(size_type a_index, set_index a_setIndex) const
  {
    return (*m_coordSets[a_setIndex])[a_index];
  }

  void TextureAnimator::
    DoResizeSetToAccomodate(set_index a_index)
  {
    if (a_index >= m_coordSets.size())
    { m_coordSets.push_back(cont_type_sptr(new cont_type()) ); }
  }

  TextureAnimator::cont_type_sptr
    TextureAnimator::
    GetSpriteCoords(set_index a_setIndex) const
  {
    return m_coordSets[a_setIndex];
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureAnimator);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(texture_animator_sptr);

};};};