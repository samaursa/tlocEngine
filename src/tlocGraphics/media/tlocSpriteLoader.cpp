#include "tlocSpriteLoader.h"

#include <tlocGraphics/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.inl.h>

namespace tloc { namespace graphics { namespace media {

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

#define SPRITE_LOADER_TEMPS   typename T_ParserType
#define SPRITE_LOADER_PARAMS  T_ParserType
#define SPRITE_LOADER_TYPE    typename SpriteLoader_T<T_ParserType>

  template <SPRITE_LOADER_TEMPS>
  bool
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    IsSupported(const core_str::String& a_input)
  {
    return parser_type().IsSupported(a_input);
  }

  template <SPRITE_LOADER_TEMPS>
  SPRITE_LOADER_TYPE::error_type
    SpriteLoader_T<SPRITE_LOADER_PARAMS>::
    Init(const string_type& a_fileContents)
  {
    m_spriteInfo.clear();
    return parser_type().Parse(a_fileContents, m_spriteInfo);
  }

  //------------------------------------------------------------------------
  // explicit instantiations

  template class SpriteLoader_T<p_sprite_loader::parser::SpriteSheetPacker>;

};};};