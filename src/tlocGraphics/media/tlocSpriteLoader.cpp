#include "tlocSpriteLoader.h"

#include <tlocGraphics/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.inl.h>

#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

namespace tloc { namespace graphics { namespace media {

  enum {
    k_initialized,
    k_count
  };

  namespace p_sprite_loader { namespace parser {

    bool
      SpriteSheetPacker::
      IsSupported(const core_str::String& a_input)
    {
      core_str::String firstLine = a_input.substr(0, a_input.find('\n'));

      core_conts::Array<core_str::String> firstLineTokens;
      core_str::Tokenize(firstLine.c_str(), ' ', firstLineTokens);

      // The file is setup such that:
      // - first token == name
      // - second token == equal-to character '='
      // - third to sixth token == numbers

      if (firstLineTokens.size() != 6)
      { return false; }

      if (firstLineTokens[0].length() == 0)
      { return false; }

      if (firstLineTokens[1].compare("=") != 0)
      { return false; }

      for (int i = 2; i <= 5; ++i)
      {
        if (core_str::IsNumber(firstLineTokens[i].c_str()) == false)
        { return false; }
      }

      return true;
    }

    core_err::Error
      SpriteSheetPacker::
      Parse(const core_str::String& a_input,
            core_conts::Array<SpriteInfo>& a_out)
    {
      typedef core_conts::Array<core_str::String>   string_array;

      string_array allLines;
      core_str::Tokenize(a_input.c_str(), '\n', allLines);

      string_array::iterator itr = allLines.begin();
      string_array::iterator itrEnd = allLines.end();

      string_array eachLine;

      while (itr != itrEnd)
      {
        if (IsSupported(*itr) == false)
        { return TLOC_ERROR(gfx_err::error_sprite_sheet_parse_error); }

        eachLine.clear();
        core_str::Tokenize(itr->c_str(), ' ', eachLine);

        SpriteInfo si;
        si.m_name = eachLine[0];
        si.m_startingPos[0] = atoi(eachLine[2].c_str());
        si.m_startingPos[1] = atoi(eachLine[3].c_str());
        si.m_endingPos[0]   = atoi(eachLine[4].c_str());
        si.m_endingPos[1]   = atoi(eachLine[5].c_str());

        a_out.push_back(si);

        ++itr;
      }

      return ErrorSuccess;
    }

  };};

  // ///////////////////////////////////////////////////////////////////////
  // SpriteLoader

#define SPRITE_LOADER_TEMPS   typename T_ParserType
#define SPRITE_LOADER_PARAMS  T_ParserType
#define SPRITE_LOADER_TYPE    typename SpriteLoader_T<T_ParserType>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    SpriteLoader_T()
    : m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  bool
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    IsSupported(const core_str::String& a_input) const
  {
    return parser_type().IsSupported(a_input);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::error_type
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    Init(const string_type& a_fileContents, dim_type a_imageDimensions)
  {
    m_spriteInfo.clear();
    error_type err = parser_type().Parse(a_fileContents, m_spriteInfo);
    if (err == ErrorSuccess)
    {
      using math::range_s32;
      using math::range_f32;

      typedef math_utils::scale_f32_s32     range_type;

      range_s32 spriteRangeX(0, a_imageDimensions[gfx_t::dimension::width]);
      range_s32 spriteRangeY(0, a_imageDimensions[gfx_t::dimension::height]);

      range_f32 texRange(0.0f, 1.0f);

      range_type texToSpriteX =
        range_type( range_type::range_small(texRange),
                    range_type::range_large(spriteRangeX) );

      range_type texToSpriteY =
        range_type( range_type::range_small(texRange),
                    range_type::range_large(spriteRangeY) );

      iterator itr = m_spriteInfo.begin();
      iterator itrEnd = m_spriteInfo.end();

      while (itr != itrEnd)
      {
        itr->m_texCoordStart[0] = texToSpriteX.ScaleDown(itr->m_startingPos[0]);
        itr->m_texCoordStart[1] = texToSpriteY.ScaleDown(itr->m_startingPos[1]);

        itr->m_texCoordEnd[0] = itr->m_texCoordStart[0] +
                                texToSpriteX.ScaleDown(itr->m_endingPos[0]);
        itr->m_texCoordEnd[1] = itr->m_texCoordStart[1] +
                                texToSpriteY.ScaleDown(itr->m_endingPos[1]);

        // sprite sheet packer y-coord starts from the top, OpenGL start
        // from the bottom, so we need to flip the y-coords
        itr->m_texCoordStart[1] = 1.0f + Mathf32::EPSILON - itr->m_texCoordStart[1];
        itr->m_texCoordEnd[1]   = 1.0f + Mathf32::EPSILON - itr->m_texCoordEnd[1];

        ++itr;
      }

      m_flags.Mark(k_initialized);
    }

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  bool
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    IsInitialized() const
  {
    return m_flags.IsMarked(k_initialized);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  struct nameMatch
  {
    nameMatch(const char* a_name)
      : m_name (a_name)
    { }

    bool operator()(const SpriteInfo& a_si)
    {
      if (a_si.m_name.find(m_name) != core_str::String::npos)
      {
        return true;
      }

      return false;
    }

    const char* m_name;
  };

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    begin(const string_type& a_name)
  {
    return core::find_if_all(m_spriteInfo, nameMatch(a_name.c_str()));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    end(const string_type& a_name)
  {
    iterator itr =
      core::find_if_end(m_spriteInfo.begin(), m_spriteInfo.end(),
                        nameMatch(a_name.c_str()));

    // end iterator must be past-the-end, ensure that this is the case
    if (itr != m_spriteInfo.end())
    { ++itr; }

    return itr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::const_iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    begin(const string_type& a_name) const
  {
    return core::find_if_all(m_spriteInfo, nameMatch(a_name.c_str()));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::const_iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    end(const string_type& a_name) const
  {
    const_iterator itr =
      core::find_if_end(m_spriteInfo.begin(), m_spriteInfo.end(),
                        nameMatch(a_name.c_str()));

    // end iterator must be past-the-end, ensure that this is the case
    if (itr != m_spriteInfo.end())
    { ++itr; }

    return itr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    begin()
  { return m_spriteInfo.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    end()
  { return m_spriteInfo.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::const_iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    begin() const
  { return m_spriteInfo.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::const_iterator
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    end() const
  { return m_spriteInfo.end(); }

  //------------------------------------------------------------------------
  // explicit instantiations

  template class SpriteLoader_T<p_sprite_loader::parser::SpriteSheetPacker>;

};};};