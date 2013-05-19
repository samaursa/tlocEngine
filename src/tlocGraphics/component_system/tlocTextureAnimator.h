#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/types/tlocStrongType.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace graphics { namespace component_system {

  class TextureAnimator
    : public core_cs::Component_T<TextureAnimator, components::texture_animator>
  {
  public:
    typedef TextureAnimator                                       this_type;
    typedef Component_T<this_type, components::texture_animator>  base_type;
    typedef f32                                                   real_type;
    typedef math_t::Vec4f32                                       vec_type;
    typedef tl_size                                               size_type;

    typedef core_conts::tl_array<vec_type>::type                cont_type;
    typedef core_sptr::SharedPtr<cont_type>                     cont_type_sptr;
    typedef core_conts::tl_array<cont_type_sptr>::type          cont_set_type;

    typedef core_t::StrongType_T<size_type, 0>                  set_index;

  public:
    TextureAnimator();
    explicit TextureAnimator(const cont_set_type& a_coords);

    // adds coord and returns its index
    size_type AddSpriteCoord(const vec_type& a_coord,
                       set_index a_setIndex = set_index(0));
    void      ModifySpriteCoord(const vec_type& a_coord, size_type a_index,
                          set_index a_setIndex = set_index(0));
    void      ModifySpriteCoords(const cont_type& a_coords,
                           set_index a_setIndex = set_index(0));
    void      RemoveSpriteCoord(size_type a_index,
                          set_index a_setIndex = set_index(0));
    void      ClearSpriteCoords(set_index a_setIndex = set_index(0));
    vec_type  GetSpriteCoord(size_type a_index,
                       set_index a_setIndex = set_index(0)) const;

    cont_type_sptr GetSpriteCoords(set_index a_setIndex = set_index(0)) const;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSpriteSets, m_coordSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentSpriteSet, m_currentSet);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentFrame, m_currentFrame);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetFPS, m_fps);
    TLOC_DECL_AND_DEF_GETTER(bool, IsLooping, m_loop);
    TLOC_DECL_AND_DEF_GETTER(tl_float, GetStartTime, m_startTime);

    TLOC_DECL_AND_DEF_SETTER(size_type, SetCurrentSpriteSet, m_currentSet);
    TLOC_DECL_AND_DEF_SETTER(size_type, SetCurrentFrame, m_currentFrame);
    TLOC_DECL_AND_DEF_SETTER(size_type, SetFPS, m_fps);
    TLOC_DECL_AND_DEF_SETTER(bool, SetLooping, m_loop);
    TLOC_DECL_AND_DEF_SETTER(tl_float, SetStartTime, m_startTime);
  private:
    void      DoResizeSetToAccomodate(set_index a_index);

  private:
    cont_set_type     m_coordSets;
    size_type         m_currentSet;
    size_type         m_currentFrame;
    size_type         m_fps;
    bool              m_loop;
    tl_float          m_startTime;

    // padding

    // in animation ->  list of numbers (go from one frame to another in any order)
    // in animation -> current frame
    // time interval -> deltaT for the whole animation?
    // duration OR FPS
    // loop -> bool
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(TextureAnimator, texture_animator);
  TLOC_TYPEDEF_COMPONENT_POOL(texture_animator_sptr, texture_animator_sptr);

};};};

#endif