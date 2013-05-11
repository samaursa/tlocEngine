#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_COORDS_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_COORDS_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

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
    typedef math_t::Vector2<real_type>                          vec_type;
    typedef core_conts::tl_array<vec_type>::type                cont_type;
    typedef tl_size                                             size_type;

  public:
    TextureCoords();
    explicit TextureCoords(const cont_type& a_coords);

    // adds coord and returns its index
    size_type AddCoord(const vec_type& a_coord);
    void      ModifyCoord(const vec_type& a_coord, size_type a_index);
    vec_type  GetCoord(size_type a_index) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(cont_type, GetCoords, m_coords);

  private:
    cont_type m_coords;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(TextureCoords, texture_coords);
  TLOC_TYPEDEF_COMPONENT_POOL(texture_coords_sptr, texture_coords_sptr);

};};};

#endif