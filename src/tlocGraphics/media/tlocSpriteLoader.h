#ifndef _TLOC_GRAPHICS_SPRITE_LOADER_H_
#define _TLOC_GRAPHICS_SPRITE_LOADER_H_

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocGraphics/types/tlocDimension.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace graphics { namespace media {

  struct SpriteInfo
  {
    core_str::String      m_name;
    core_ds::Tuple2s32    m_startingPos;
    core_ds::Tuple2s32    m_endingPos;

    math_t::Vec2f32       m_texCoordStart;
    math_t::Vec2f32       m_texCoordEnd;
  };

  namespace p_sprite_loader
  {
    namespace parser {

      struct SpriteSheetPacker
      {
        bool            IsSupported(const core_str::String& a_input);
        core_err::Error Parse(const core_str::String& a_input,
                              core_conts::Array<SpriteInfo>& a_out);
      };
    };
  };

  template <typename T_ParserType>
  class SpriteLoader_T
  {
  public:
    typedef T_ParserType                          parser_type;
    typedef core_err::Error                       error_type;
    typedef core_str::String                      string_type;
    typedef types::Dimension2i                    dim_type;

    typedef core_conts::Array<SpriteInfo>               sprite_info_cont;
    typedef typename sprite_info_cont::size_type        size_type;
    typedef typename sprite_info_cont::iterator         iterator;
    typedef typename sprite_info_cont::const_iterator   const_iterator;

  public:
    SpriteLoader_T();

    bool       IsSupported(const string_type& a_input);
    error_type Init(const string_type& a_fileContents,
                    dim_type a_imageDimensions);

    bool       IsInitialized() const;

    const_iterator  begin() const;
    const_iterator  end() const;

    const_iterator  begin(const string_type& a_name) const;
    const_iterator  end(const string_type& a_name) const;

    TLOC_DECL_AND_DEF_GETTER(sprite_info_cont, GetSpriteInfo, m_spriteInfo);

  private:
    sprite_info_cont        m_spriteInfo;
    core_ds::Tuple2s32      m_imageDimensions;
    core_utils::Checkpoints m_flags;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef SpriteLoader_T
    <p_sprite_loader::parser::SpriteSheetPacker> SpriteLoader_SpriteSheetPacker;

};};};

#endif