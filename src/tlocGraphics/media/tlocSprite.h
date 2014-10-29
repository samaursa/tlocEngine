#ifndef _TLOC_GRAPHICS_MEDIA_SPRITE_H_
#define _TLOC_GRAPHICS_MEDIA_SPRITE_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/media/tlocSpriteInfo.h>
#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  template <typename T_NameType>
  class SpriteSheet_T
  {
  public:
    typedef T_NameType                                name_type;
    typedef SpriteSheet_T<name_type>                  this_type;

    typedef SpriteInfo_T<name_type>                   sprite_info_type;
    typedef gfx_med::image_sptr                       image_ptr;

    typedef core_conts::Array<sprite_info_type>       sprite_info_cont;
    typedef typename sprite_info_cont::iterator       iterator;
    typedef typename sprite_info_cont::const_iterator const_iterator;

  public:
    SpriteSheet_T();
    SpriteSheet_T(image_ptr a_spriteSheet, sprite_info_cont a_spriteSheetInfo);

    const_iterator begin() const;
    const_iterator end() const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(image_ptr, GetSpriteSheet, m_spriteSheet);

  private:
    image_ptr           m_spriteSheet;
    sprite_info_cont    m_spriteSheetInfo;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef SpriteSheet_T<core_str::String>                 sprite_sheet_str;
  typedef SpriteSheet_T<tl_ulong>                         sprite_sheet_ul;

  TLOC_TYPEDEF_ALL_SMART_PTRS(sprite_sheet_str, sprite_sheet_str);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(sprite_sheet_str, sprite_sheet_str);

  TLOC_TYPEDEF_ALL_SMART_PTRS(sprite_sheet_ul, sprite_sheet_ul);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(sprite_sheet_ul, sprite_sheet_ul);

  // -----------------------------------------------------------------------
  // extern template 

  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<core_str::String>);
  TLOC_EXTERN_TEMPLATE_CLASS(SpriteInfo_T<tl_ulong>);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(sprite_sheet_str);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(sprite_sheet_str);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(sprite_sheet_ul);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(sprite_sheet_ul);

};};};

#endif