#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/base_classes/tlocPolicyBase.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#include <tlocGraphics/media/tlocFont.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextAlignment.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Text_I
  {
  public:
    typedef Text_I                                          this_type;

    typedef core_str::StringW                               str_type;
    typedef alignment::align_type                           align_type;
    typedef gfx_med::font_sptr                              font_ptr;
    typedef tl_float                                        real_type;

  public:

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(BufferArgW, Set, m_text);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, Get, m_text);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(font_ptr, GetFont, m_font);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(font_ptr, SetFont, m_font);

    TLOC_DECL_AND_DEF_GETTER(real_type, GetVerticalKerning, m_verticalKerning);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(real_type, SetVerticalKerning, m_verticalKerning);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(align_type, SetAlignment, m_alignment);
    TLOC_DECL_AND_DEF_GETTER(align_type, GetAlignment, m_alignment);

  protected:
    Text_I();
    ~Text_I();
    explicit Text_I(BufferArgW a_text, 
                    font_ptr a_font,
                    align_type a_alignment = alignment::k_align_left);

  private:
    str_type                m_text;
    real_type               m_verticalKerning;
    align_type              m_alignment;
    font_ptr                m_font;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_VIRTUAL_PTR(Text_I, text_i);

};};};

#endif