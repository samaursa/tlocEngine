#include "tlocSpriteInfo.h"

#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // SpriteInfoBase_I

  SpriteInfoBase_I::
    SpriteInfoBase_I()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SpriteInfoBase_I::
    SpriteInfoBase_I( pos_type a_startingPos, pos_type a_dimensions )
    : m_startingPos(a_startingPos)
    , m_dimensions(a_dimensions)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SpriteInfoBase_I::
    ~SpriteInfoBase_I()
  { }

  void
    SpriteInfoBase_I::
    ComputeTexCoords( dim_type a_imgDimensions,
                      p_sprite_info::FlipYCoords a_flip)
  {
    if (m_dimensions[0] == 0 || m_dimensions[1] == 0)
    { 
      m_texCoordStart.Set(0);
      m_texCoordEnd.Set(0);
      return;
    }

    TLOC_ASSERT(m_dimensions[0] > 0 && m_dimensions[1] > 0,
                "Invalid dimensions - dimensions cannot be 0");

    using math::range_tl_size;
    using math::Rangef;

    typedef math_utils::scale_f32_tl_size                 range_type;

    range_tl_size spriteRangeX( 0, a_imgDimensions[gfx_t::dimension::width] + 1 );
    range_tl_size spriteRangeY( 0, a_imgDimensions[gfx_t::dimension::height] + 1 );

    Rangef texRange(0.0f, 2.0f);

    range_type  texToSpriteX =
      range_type( range_type::range_small(texRange),
                  range_type::range_large(spriteRangeX) );

    range_type  texToSpriteY =
      range_type( range_type::range_small( texRange ),
                  range_type::range_large( spriteRangeY ) );

    // we need to include the last row and col due to precision errors
    // NOTE: You should have at least 1 pixel transparent padding around each
    // sprite
    const f32 oneRow = texToSpriteX.ScaleDown( 1 );
    const f32 oneCol = texToSpriteY.ScaleDown( 1 );

    m_texCoordStart[0] = texToSpriteX.ScaleDown( m_startingPos[0] );
    m_texCoordStart[1] = texToSpriteY.ScaleDown( m_startingPos[1] );

    m_texCoordEnd[0] = m_texCoordStart[0] + oneRow +
      texToSpriteX.ScaleDown( m_dimensions[0] - 1 );
    m_texCoordEnd[1] = m_texCoordStart[1] + oneCol +
      texToSpriteY.ScaleDown( m_dimensions[1] - 1 );

    // most sprite packers' y-coord starts from the top, OpenGL's start from
    // the bottom, so we need to flip the y-coords
    if (a_flip)
    {
      m_texCoordStart[1] = 1.0f + Mathf::EPSILON - m_texCoordStart[1];
      m_texCoordEnd[1] = 1.0f + Mathf::EPSILON - m_texCoordEnd[1];
    }
  }

  // -----------------------------------------------------------------------
  // algos

  namespace algos { namespace compare {
    namespace sprite_info {

      // ///////////////////////////////////////////////////////////////////////
      // NameBegins

      NameBegins::
        NameBegins(BufferArg a_name)
        : m_name( a_name )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool
        NameBegins::
        operator ()( const value_type& a_si )
      {
        typedef str_type::size_type      size_type;

        const size_type siNameLength = a_si.GetName().length();
        const size_type compNameLength = core_str::StrLen( m_name.GetPtr() );

        if ( siNameLength < compNameLength )
        { return false; }

        if ( a_si.GetName().compare( 0, compNameLength, m_name ) == 0 )
        {
          return true;
        }

        return false;
      }

    };
  };};

};};};

using namespace tloc::gfx_med;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(sprite_info_str);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(sprite_info_str);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(sprite_info_ul);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(sprite_info_ul);