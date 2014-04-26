#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextAlignment.h>
#include <tlocGraphics/component_system/tlocText_I.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class StaticText
    : public core_cs::Component_T<StaticText, components::static_text>
    , public Text_I
  {
  public:
    typedef StaticText                                      this_type;
    typedef Component_T<this_type, components::static_text> base_type;

  public:
    StaticText();
    explicit StaticText(BufferArgW a_text, 
                        font_ptr a_font,
                        align_type a_alignment = alignment::k_align_left);

    void SetAlignment(align_type a_alignment);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(StaticText, static_text);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(StaticText, static_text);
  TLOC_TYPEDEF_COMPONENT_POOL(StaticText, static_text);

};};};

#endif