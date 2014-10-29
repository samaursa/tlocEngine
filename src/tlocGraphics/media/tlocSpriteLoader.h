#ifndef _TLOC_GRAPHICS_SPRITE_LOADER_H_
#define _TLOC_GRAPHICS_SPRITE_LOADER_H_

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/types/tlocDimension.h>
#include <tlocGraphics/media/tlocSpriteInfo.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace graphics { namespace media {

  namespace p_sprite_loader
  {
    namespace parser {

      using core_str::String;
      using types::Dimension2;

      // ///////////////////////////////////////////////////////////////////////
      // SpriteSheetPacker

      struct SpriteSheetPacker
      {
        bool            IsSupported(const String& a_input);
        core_err::Error Parse(const String& a_input,
                              const Dimension2 a_imgDim,
                              core_conts::Array<sprite_info_str>& a_out);
      };

      // ///////////////////////////////////////////////////////////////////////
      // TexturePacker

      struct TexturePacker
      {
        bool            IsSupported(const String& a_input);
        core_err::Error Parse(const String& a_input,
                              const Dimension2 a_imgDim,
                              core_conts::Array<sprite_info_str>& a_out);
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
    typedef types::Dimension2                     dim_type;
    typedef sprite_info_str                       sprite_info_type;

    typedef core_conts::Array<sprite_info_type>         sprite_info_cont;
    typedef typename sprite_info_cont::size_type        size_type;
    typedef typename sprite_info_cont::iterator         iterator;
    typedef typename sprite_info_cont::const_iterator   const_iterator;

  public:
    SpriteLoader_T();

    bool            IsSupported(const string_type& a_input) const;
    error_type      Init(const string_type& a_fileContents,
                         dim_type a_imageDimensions);

    bool            IsInitialized() const;

    iterator        begin();
    iterator        end();
    const_iterator  begin() const;
    const_iterator  end() const;

    iterator        begin(BufferArg a_name);
    iterator        end(BufferArg a_name);
    const_iterator  begin(BufferArg a_name) const;
    const_iterator  end(BufferArg a_name) const;

    TLOC_DECL_AND_DEF_GETTER(sprite_info_cont, GetSpriteInfo, m_spriteInfo);
    TLOC_DECL_AND_DEF_GETTER(dim_type, GetDimensions, m_imageDimensions);

  private:
    sprite_info_cont        m_spriteInfo;
    dim_type                m_imageDimensions;
    core_utils::Checkpoints m_flags;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef SpriteLoader_T
    <p_sprite_loader::parser::SpriteSheetPacker> SpriteLoader_SpriteSheetPacker;
  typedef SpriteLoader_T
    <p_sprite_loader::parser::TexturePacker>     SpriteLoader_TexturePacker;

  TLOC_TYPEDEF_ALL_SMART_PTRS(SpriteLoader_SpriteSheetPacker, sprite_loader_sprite_sheet_packer);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SpriteLoader_SpriteSheetPacker, sprite_loader_sprite_sheet_packer);

  TLOC_TYPEDEF_ALL_SMART_PTRS(SpriteLoader_TexturePacker, sprite_loader_texture_packer);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SpriteLoader_TexturePacker, sprite_loader_texture_packer);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(SpriteLoader_T<p_sprite_loader::parser::SpriteSheetPacker>);
  TLOC_EXTERN_TEMPLATE_CLASS(SpriteLoader_T<p_sprite_loader::parser::TexturePacker>);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::SpriteLoader_SpriteSheetPacker);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::SpriteLoader_SpriteSheetPacker);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::SpriteLoader_TexturePacker);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::SpriteLoader_TexturePacker);

#endif