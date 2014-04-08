#include "tlocSprite.h"

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // SpriteInfo_T<>

#define TLOC_SPRITE_SHEET_TEMPS    typename T_NameType
#define TLOC_SPRITE_SHEET_PARAMS   T_NameType
#define TLOC_SPRITE_SHEET_TYPE     typename SpriteSheet_T<TLOC_SPRITE_SHEET_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_SPRITE_SHEET_TEMPS>
  SpriteSheet_T<TLOC_SPRITE_SHEET_PARAMS>::
    SpriteSheet_T()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_SPRITE_SHEET_TEMPS>
  SpriteSheet_T<TLOC_SPRITE_SHEET_PARAMS>::
    SpriteSheet_T(image_ptr a_spriteSheet, sprite_info_cont a_spriteSheetInfo)
    : m_spriteSheet(a_spriteSheet)
    , m_spriteSheetInfo(a_spriteSheetInfo)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_SPRITE_SHEET_TEMPS>
  TLOC_SPRITE_SHEET_TYPE::const_iterator
    SpriteSheet_T<TLOC_SPRITE_SHEET_PARAMS>::
    begin() const
  {
    TLOC_ASSERT(m_spriteSheet.IsValid(), "SpriteSheet image is not valid");
    return m_spriteSheetInfo.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_SPRITE_SHEET_TEMPS>
  TLOC_SPRITE_SHEET_TYPE::const_iterator
    SpriteSheet_T<TLOC_SPRITE_SHEET_PARAMS>::
    end() const
  {
    TLOC_ASSERT(m_spriteSheet.IsValid(), "SpriteSheet image is not valid");
    return m_spriteSheetInfo.end();
  }

};};};

using namespace tloc::gfx_med;

#include <tlocCore/containers/tlocArray.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(sprite_sheet_str::sprite_info_cont);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(sprite_sheet_ul::sprite_info_cont);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(sprite_sheet_str);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(sprite_sheet_str);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(sprite_sheet_ul);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(sprite_sheet_ul);