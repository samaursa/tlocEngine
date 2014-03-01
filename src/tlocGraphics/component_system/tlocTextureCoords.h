#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_COORDS_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_COORDS_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/types/tlocStrongType.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace graphics { namespace component_system {

  class TextureCoords
    : public core_cs::Component_T<TextureCoords, components::texture_coords>
  {
  public:
    typedef TextureCoords                                       this_type;
    typedef Component_T<this_type, components::texture_coords>  base_type;
    typedef f32                                                 real_type;
    typedef math_t::Vec2f32                                     vec_type;
    typedef core_conts::tl_array<vec_type>::type                cont_type;
    typedef core_sptr::SharedPtr<cont_type>                     cont_type_sptr;
    typedef core_conts::tl_array<cont_type_sptr>::type          cont_set_type;
    typedef tl_size                                             size_type;

    typedef core_t::StrongType_T<size_type, 0>                  set_index;

  public:
    TextureCoords();
    explicit TextureCoords(const cont_set_type& a_coords);

    // adds coord and returns its index
    size_type AddCoord(const vec_type& a_coord,
                       set_index a_setIndex = set_index(0));
    void      ModifyCoord(const vec_type& a_coord, size_type a_index,
                          set_index a_setIndex = set_index(0));
    void      ModifyCoords(const cont_type& a_coords,
                           set_index a_setIndex = set_index(0));
    void      RemoveCoord(size_type a_index,
                          set_index a_setIndex = set_index(0));
    void      ClearCoords(set_index a_setIndex = set_index(0));
    vec_type  GetCoord(size_type a_index,
                       set_index a_setIndex = set_index(0)) const;

    cont_type_sptr GetCoords(set_index a_setIndex = set_index(0)) const;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSets, m_coordSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentSet, m_currentSet);

    TLOC_DECL_AND_DEF_SETTER(size_type, SetCurrentSet, m_currentSet);
  private:
    void      DoResizeSetToAccomodate(set_index a_index);

  private:
    cont_set_type  m_coordSets;
    size_type      m_currentSet;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(TextureCoords, texture_coords);
  TLOC_TYPEDEF_COMPONENT_POOL(TextureCoords, texture_coords);

};};};

#endif