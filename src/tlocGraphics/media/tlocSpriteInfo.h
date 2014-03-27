#ifndef _TLOC_GRAPHICS_SPRITE_INFO_H_
#define _TLOC_GRAPHICS_SPRITE_INFO_H_

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocGraphics/types/tlocDimension.h>

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // SpriteInfoBase_I

  namespace p_sprite_info
  {
    struct FlipYCoords
    {
      FlipYCoords(bool a_flip = true)
        : m_flip(a_flip)
      { }

      operator bool()
      { return m_flip; }

      bool m_flip;
    };
  };

  class SpriteInfoBase_I
  {
  public:
    typedef core_ds::Tuple2s                              pos_type;
    typedef math_t::Vec2f                                 coord_type;
    typedef gfx_t::Dimension2                             dim_type;
    typedef p_sprite_info::FlipYCoords                    flip_coords;
    
  protected:
    SpriteInfoBase_I();
    SpriteInfoBase_I( pos_type a_startingPos, pos_type a_dimensions );
    ~SpriteInfoBase_I();

    void ComputeTexCoords( dim_type a_imgDimensions, 
                           flip_coords a_flip = flip_coords());

    TLOC_DECL_AND_DEF_GETTER( pos_type, GetStartingPos, m_startingPos );
    TLOC_DECL_AND_DEF_GETTER( pos_type, GetDimensions, m_dimensions );

    TLOC_DECL_AND_DEF_GETTER( coord_type, GetTexCoordStart, m_texCoordStart );
    TLOC_DECL_AND_DEF_GETTER( coord_type, GetTexCoordEnd, m_texCoordEnd );

  private:
    pos_type          m_startingPos;
    pos_type          m_dimensions;

    coord_type        m_texCoordStart;
    coord_type        m_texCoordEnd;
  };

  // ///////////////////////////////////////////////////////////////////////
  // SpriteInfo_T<>

  template <typename T_NameType>
  class SpriteInfo_T
    : public SpriteInfoBase_I
  {
    typedef SpriteInfoBase_I                      base_type;
    typedef T_NameType                            name_type;
    typedef type_traits::CallTraits<name_type>    name_param;

  public:
    SpriteInfo_T();
    SpriteInfo_T(name_param a_name,
                 pos_type a_startingPos, pos_type a_dimensions);

    TLOC_DECL_AND_DEF_GETTER(name_param, GetName, m_name);

  private:
    name_param                   m_name;
  };

  namespace algos { namespace compare {
    namespace sprite_info {

      // ///////////////////////////////////////////////////////////////////////
      // Name<>

      template <typename T_NameType>
      struct Name
      {
      public:
        typedef T_NameType                                      name_type;
        typedef typename 
          type_traits::CallTraits<name_type>::param_type        name_param;

        typedef SpriteInfo_T<name_type>                         value_type;

      public:
        Name(name_param a_name)
          : m_name(a_name)
        { }

        bool operator()( const value_type& a_other )
        {
          return core::equal_to<value_type>()(a_other.GetName(), a_name);
        }

      private:
        name_param a_name;
      };

      // -----------------------------------------------------------------------
      // MakeName helper function

      template <typename T_NameType>
      Name<T_NameType>
        MakeName( typename type_traits::CallTraits<T_NameType>::param_type
                  a_name)
      { 
        return Name<T_NameType>();
      }
      
    };
  };};

};};};

#endif