#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

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
    struct CoordSet
    {
      CoordSet();
      CoordSet(const CoordSet& a_other);
      explicit CoordSet(const TextureCoords& a_coords);

      CoordSet& operator=(const CoordSet& a_other)
      {
        CoordSet temp(a_other);
        core::swap(m_coords,    temp.m_coords);
        core::swap(m_frameDeltaT,       temp.m_frameDeltaT);
        core::swap(m_startTime, temp.m_startTime);
        core::swap(m_flags,     temp.m_flags);

        return *this;
      }

      TextureCoords           m_coords;
      tl_float                m_frameDeltaT;
      f64                     m_startTime;
      f64                     m_totalTime;
      core_utils::Checkpoints m_flags;
    };

  public:
    typedef TextureAnimator                                       this_type;
    typedef Component_T<this_type, components::texture_animator>  base_type;
    typedef f32                                                   real_type;
    typedef CoordSet                                              coord_set;
    typedef gfx_t::Dimension2u                                    dim_type;
    typedef tl_size                                               size_type;

    typedef core_conts::tl_array<coord_set>::type               cont_type;

  public:
    TextureAnimator();

    void            AddSpriteSet(const TextureCoords& a_coords);
    void            ModifySpriteSet(const TextureCoords& a_coords,
                                    size_type a_index);
    void            RemoveSpriteSet(size_type a_index);

    TextureCoords&       GetSpriteSequence(size_type a_index);
    const TextureCoords& GetSpriteSequence(size_type a_index) const;
    TextureCoords&       GetCurrentSpriteSequence();
    const TextureCoords& GetCurrentSpriteSequence() const;

    void            NextFrame();
    void            PrevFrame();
    void            SetFrame(size_type a_index);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSpriteSequences, m_coordSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentSpriteSeqIndex, m_currentSet);
    TLOC_DECL_AND_DEF_GETTER(f64,  GetStartTime, m_coordSets[m_currentSet].m_startTime);
    TLOC_DECL_AND_DEF_GETTER(f64,  GetTotalTime, m_coordSets[m_currentSet].m_totalTime);
    TLOC_DECL_AND_DEF_GETTER(f64,  GetFrameDeltaT, m_coordSets[m_currentSet].m_frameDeltaT);

    TLOC_DECL_GETTER(bool, IsLooping);
    TLOC_DECL_GETTER(bool, IsPaused);
    TLOC_DECL_GETTER(bool, IsStopped);
    TLOC_DECL_GETTER(bool, IsLastFrame);
    TLOC_DECL_GETTER(bool, IsSpriteSeqChanged);
    TLOC_DECL_GETTER(size_type, GetFPS);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE
      (f64,  SetStartTime, m_coordSets[m_currentSet].m_startTime);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE
      (f64,  SetTotalTime, m_coordSets[m_currentSet].m_totalTime);

    TLOC_DECL_SETTER_BY_VALUE(bool, SetLooping);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetPaused);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetStopped);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetSpriteSequenceChanged);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetCurrentSpriteSequence);
    TLOC_DECL_SETTER_BY_VALUE(size_type, SetFPS);

  private:
    cont_type         m_coordSets;
    size_type         m_currentSet;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(TextureAnimator, texture_animator);
  TLOC_TYPEDEF_COMPONENT_POOL(TextureAnimator, texture_animator);

};};};

#endif