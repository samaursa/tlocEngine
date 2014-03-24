#ifndef _TLOC_GRAPHICS_SPRITE_LOADER_H_
#define _TLOC_GRAPHICS_SPRITE_LOADER_H_

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/types/tlocDimension.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace graphics { namespace media {

  struct SpriteInfo
  {
    typedef core_str::String      string_type;

    string_type           m_name;
    core_ds::Tuple2s32    m_startingPos;
    core_ds::Tuple2s32    m_dimensions;

    math_t::Vec2f32       m_texCoordStart;
    math_t::Vec2f32       m_texCoordEnd;
  };

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
                              core_conts::Array<SpriteInfo>& a_out);
      };

      // ///////////////////////////////////////////////////////////////////////
      // TexturePacker

      struct TexturePacker
      {
        bool            IsSupported(const String& a_input);
        core_err::Error Parse(const String& a_input,
                              const Dimension2 a_imgDim,
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
    typedef types::Dimension2                     dim_type;

    typedef core_conts::Array<SpriteInfo>               sprite_info_cont;
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

  // -----------------------------------------------------------------------
  // algorithms

  namespace algos { namespace compare { namespace sprite_info {

      struct Name
      {
        typedef SpriteInfo                    value_type;

        Name(BufferArg a_nameToSearch)
          : m_nameToSearch(a_nameToSearch)
        { }

        bool operator()(const value_type& a_other)
        {
          return a_other.m_name.compare(m_nameToSearch) == 0;
        }

        BufferArg m_nameToSearch;
      };

      struct NameBegins
      {
        typedef SpriteInfo                    value_type;

        NameBegins(BufferArg a_nameToSearch)
          : m_name (a_nameToSearch)
        { }

      // if the sprite name begins with a_nameToSearch, return true
        bool operator()(const value_type& a_si)
        {
          typedef SpriteInfo::string_type::size_type      size_type;

          const size_type siNameLength = a_si.m_name.length();
          const size_type compNameLength = core_str::StrLen(m_name.GetPtr());

          if (siNameLength < compNameLength)
          { return false; }

          if (a_si.m_name.compare(0, compNameLength, m_name) == 0)
          {
            return true;
          }

          return false;
        }

        BufferArg m_name;
      };

  };};};

};};};

#endif