#ifndef _TLOC_GRAPHICS_SPRITE_INFO_H_
#define _TLOC_GRAPHICS_SPRITE_INFO_H_

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/string/tlocString.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

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

  public:
    void ComputeTexCoords( dim_type a_imgDimensions,
                           flip_coords a_flip = flip_coords());

    TLOC_DECL_AND_DEF_GETTER( pos_type, GetStartingPos, m_startingPos );
    TLOC_DECL_AND_DEF_GETTER( pos_type, GetDimensions, m_dimensions );

    TLOC_DECL_AND_DEF_GETTER( coord_type, GetTexCoordStart, m_texCoordStart );
    TLOC_DECL_AND_DEF_GETTER( coord_type, GetTexCoordEnd, m_texCoordEnd );

  protected:
    SpriteInfoBase_I();
    SpriteInfoBase_I(pos_type a_startingPos, pos_type a_dimensions);
    ~SpriteInfoBase_I();

  private:
    pos_type          m_startingPos;
    dim_type          m_dimensions;

    coord_type        m_texCoordStart;
    coord_type        m_texCoordEnd;
  };

  // ///////////////////////////////////////////////////////////////////////
  // SpriteInfo_T<>

  template <typename T_NameType>
  class SpriteInfo_T
    : public SpriteInfoBase_I
  {
  public:
    typedef SpriteInfoBase_I                                base_type;
    typedef base_type::pos_type                             pos_type;
    typedef base_type::dim_type                             dim_type;

    typedef T_NameType                                      name_type;
    typedef typename
      type_traits::CallTraits<name_type>::param_type        name_param;

  public:
    SpriteInfo_T();
    SpriteInfo_T(name_param a_name,
                 pos_type a_startingPos, dim_type a_dimensions);

    TLOC_DECL_AND_DEF_GETTER(name_param, GetName, m_name);

  private:
    name_type                   m_name;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_NameType>
  SpriteInfo_T<T_NameType>::
    SpriteInfo_T()
    : base_type()
  { }

  template <typename T_NameType>
  SpriteInfo_T<T_NameType>::
    SpriteInfo_T(name_param a_name,
                 pos_type a_startingPos, dim_type a_dimensions)
    : base_type( a_startingPos, a_dimensions )
    , m_name(a_name)
  { }

  // -----------------------------------------------------------------------
  // typedefs

  typedef SpriteInfo_T<core_str::String>                    sprite_info_str;
  typedef SpriteInfo_T<tl_ulong>                            sprite_info_ul;

  TLOC_TYPEDEF_ALL_SMART_PTRS(sprite_info_str, sprite_infor_str);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(sprite_info_str, sprite_info_str);

  TLOC_TYPEDEF_ALL_SMART_PTRS(sprite_info_ul, sprite_info_ul);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(sprite_info_ul, sprite_info_ul);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<core_str::String> );
  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<tl_ulong>);

  // -----------------------------------------------------------------------
  // algorithms

  namespace algos { namespace transform {
    namespace sprite_info {

      // ///////////////////////////////////////////////////////////////////////
      // ComputeTexCoords

      struct ComputeTexCoords
      {
        typedef SpriteInfoBase_I                              value_type;
        typedef value_type::dim_type                          dim_type;
        typedef value_type::flip_coords                       flip_coords;

      public:
        ComputeTexCoords(dim_type a_dim, flip_coords a_flip = flip_coords())
          : m_dim(a_dim)
          , m_flip(a_flip)
        { }

        void operator()(value_type& a_si)
        { a_si.ComputeTexCoords(m_dim, m_flip); }

      private:
        dim_type      m_dim;
        flip_coords   m_flip;
      };

    };
  };};

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
          return core::equal_to<name_type>()(a_other.GetName(), m_name);
        }

      private:
        name_type m_name;
      };

      // -----------------------------------------------------------------------
      // MakeName helper function

      template <typename T_NameType>
      Name<T_NameType>
        MakeName( T_NameType a_name)
      {
        return Name<T_NameType>(a_name);
      }

      template <typename T>
      Name<core_str::StringBase<T> >
        MakeName( const T* a_name)
      {
          return Name<core_str::StringBase<T> >(a_name);
      }

      // ///////////////////////////////////////////////////////////////////////
      // NameBegins

      struct NameBegins
      {
      public:
        typedef core_str::String                              str_type;
        typedef SpriteInfo_T<str_type>                        value_type;

      public:
        NameBegins(BufferArg a_name);

        // if the sprite name begins with a_nameToSearch, return true
        bool operator()(const value_type& a_si);

        BufferArg  m_name;
      };

    };
  };};
  
  
  // -----------------------------------------------------------------------
  // extern template
  
  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<core_str::String> );
  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<tl_ulong>);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::sprite_info_str);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::sprite_info_str);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::sprite_info_ul);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::sprite_info_ul);

#endif