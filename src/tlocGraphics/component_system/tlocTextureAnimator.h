#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/types/tlocDimension.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace graphics { namespace component_system {

  class TextureAnimator
    : public core_cs::Component_T<TextureAnimator, components::texture_animator>
  {
  public:
    typedef TextureAnimator                                       this_type;
    typedef Component_T<this_type, components::texture_animator>  base_type;
    typedef f32                                                   real_type;
    typedef TextureCoords                                         coord_set;
    typedef gfx_t::Dimension2u                                    dim_type;
    typedef tl_size                                               size_type;

    typedef core_conts::tl_array<coord_set>::type               cont_type;

  public:
    TextureAnimator();

    void            AddSpriteSet(const coord_set& a_coords);
    void            ModifySpriteSet(const coord_set& a_coords,
                                    size_type a_index);
    void            RemoveSpriteCoord(size_type a_index);

    coord_set       GetSpriteSet(size_type a_index);
    const coord_set GetSpriteSet(size_type a_index) const;

    void            NextFrame();
    void            PrevFrame();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSpriteSets, m_coordSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentSpriteSetIndex, m_currentSet);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetFPS, m_fps);
    TLOC_DECL_AND_DEF_GETTER(f64,  GetStartTime, m_startTime);
    TLOC_DECL_AND_DEF_GETTER(dim_type,  GetDimensions, m_dimensions);

    TLOC_DECL_GETTER(bool, IsLooping);
    TLOC_DECL_GETTER(bool, IsPaused);
    TLOC_DECL_GETTER(bool, IsSpriteSetChanged);

    TLOC_DECL_AND_DEF_SETTER(size_type, SetFPS, m_fps);
    TLOC_DECL_AND_DEF_SETTER(f64,  SetStartTime, m_startTime);
    TLOC_DECL_AND_DEF_SETTER(dim_type,  SetDimensions, m_dimensions);

    TLOC_DECL_SETTER(bool, SetLooping);
    TLOC_DECL_SETTER(bool, SetPaused);
    TLOC_DECL_SETTER(size_type, SetCurrentSpriteSet);

  private:
    cont_type         m_coordSets;
    size_type         m_currentSet;
    size_type         m_fps;
    f64               m_startTime;
    dim_type          m_dimensions;

    core_utils::Checkpoints m_flags;

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